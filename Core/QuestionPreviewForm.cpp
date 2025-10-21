/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "QuestionPreviewForm.h"



QuestionPreviewForm::QuestionPreviewForm(QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    encodingComboBox = new QComboBox;

    QLabel *encodingLabel = new QLabel(tr("&Encoding:"));
    encodingLabel->setBuddy(encodingComboBox);

    textEdit = new QPlainTextEdit;
    textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
    textEdit->setReadOnly(true);

    QDialogButtonBox *buttonBox =
        new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    okButton = buttonBox->button(QDialogButtonBox::Ok);

    typedef void(QComboBox::*ComboBoxIntSignal)(int);
    connect(encodingComboBox, static_cast<ComboBoxIntSignal>(&QComboBox::activated),
            this, &QuestionPreviewForm::updateTextEdit);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QGridLayout *mainLayout = new QGridLayout(this);
    mainLayout->addWidget(encodingLabel, 0, 0);
    mainLayout->addWidget(encodingComboBox, 0, 1);
    tabWidget = new QTabWidget;
    tabWidget->addTab(textEdit, tr("Preview"));
    mainLayout->addWidget(tabWidget, 1, 0, 1, 2);
    statusLabel = new QLabel;
    mainLayout->addWidget(statusLabel, 2, 0, 1, 2);
    mainLayout->addWidget(buttonBox, 3, 0, 1, 2);

    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    resize(screenGeometry.width() * 2 / 5, screenGeometry.height() / 2);

    setupCodecList();
}

void QuestionPreviewForm::setupCodecList()
{
    QMap <QString, QTextCodec *> codecMap;
    QList <QTextCodec *> listCodecs;
    QRegExp iso8859RegExp("ISO[- ]8859-([0-9]+).*");

    foreach (int mib, QTextCodec::availableMibs()) {
        QTextCodec *codec = QTextCodec::codecForMib(mib);

        QString sortKey = codec->name().toUpper();
        int rank;

        if (sortKey.startsWith(QLatin1String("UTF-8"))) {
            rank = 1;
        } else if (sortKey.startsWith(QLatin1String("UTF-16"))) {
            rank = 2;
        } else if (iso8859RegExp.exactMatch(sortKey)) {
            if (iso8859RegExp.cap(1).size() == 1)
                rank = 3;
            else
                rank = 4;
        } else {
            rank = 5;
        }
        sortKey.prepend(QLatin1Char('0' + rank));

        codecMap.insert(sortKey, codec);
    }
    listCodecs = codecMap.values();

    encodingComboBox->clear();
    foreach (const QTextCodec *codec, listCodecs) {
        encodingComboBox->addItem(QLatin1String(codec->name()),QVariant(codec->mibEnum()));
    }
}

void QuestionPreviewForm::reset()
{
    decodedStr.clear();
    textEdit->clear();
    statusLabel->clear();
    statusLabel->setStyleSheet(QString());
    okButton->setEnabled(false);
    tabWidget->setCurrentIndex(0);
}

void QuestionPreviewForm::setEncodedData(const QByteArray &data)
{
    reset();
    encodedData = data;
    updateTextEdit();
}

void QuestionPreviewForm::updateTextEdit()
{
    int mib = encodingComboBox->itemData(
                      encodingComboBox->currentIndex()).toInt();
    const QTextCodec *codec = QTextCodec::codecForMib(mib);
    const QString name = QLatin1String(codec->name());

    QTextCodec::ConverterState state;
    decodedStr = codec->toUnicode(encodedData.constData(), encodedData.size(), &state);

    bool success = true;
    if (state.remainingChars) {
        success = false;
        const QString message =
            tr("%1: conversion error at character %2")
            .arg(name).arg(encodedData.size() - state.remainingChars + 1);
        statusLabel->setText(message);
        statusLabel->setStyleSheet(QStringLiteral("background-color: \"red\";"));
    } else if (state.invalidChars) {
        statusLabel->setText(tr("%1: %n invalid characters", 0, state.invalidChars).arg(name));
        statusLabel->setStyleSheet(QStringLiteral("background-color: \"yellow\";"));
    } else {
        statusLabel->setText(tr("%1: %n bytes converted", 0, encodedData.size()).arg(name));
        statusLabel->setStyleSheet(QString());
    }
    if (success)
        textEdit->setPlainText(decodedStr);
    else
        textEdit->clear();
    okButton->setEnabled(success);
}
