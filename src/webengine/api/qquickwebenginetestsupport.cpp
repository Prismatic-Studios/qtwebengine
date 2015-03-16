/****************************************************************************
**
** Copyright (C) 2015 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qquickwebenginetestsupport_p.h"

#include "qquickwebengineloadrequest_p.h"

QT_BEGIN_NAMESPACE
using namespace QtWebEngineCore;

QQuickWebEngineJavaScriptDialog::QQuickWebEngineJavaScriptDialog(QSharedPointer<JavaScriptDialogController> controller)
{
    m_dialogController = controller;
}

QString QQuickWebEngineJavaScriptDialog::message() const
{
    return m_dialogController->message();
}

QString QQuickWebEngineJavaScriptDialog::defaultValue() const
{
    return m_dialogController->defaultPrompt();
}

void QQuickWebEngineJavaScriptDialog::reject()
{
    QMetaObject::invokeMethod(m_dialogController.data(), "reject");
}

void QQuickWebEngineJavaScriptDialog::accept(const QString &input)
{
    if (!input.isNull())
        QMetaObject::invokeMethod(m_dialogController.data(), "textProvided", Q_ARG(QString, input));
    QMetaObject::invokeMethod(m_dialogController.data(), "accept");
}

QQuickWebEngineErrorPage::QQuickWebEngineErrorPage()
{
}

void QQuickWebEngineErrorPage::loadFinished(bool success, const QUrl &url)
{
    // Loading of the error page should not fail.
    Q_ASSERT(success);

    QQuickWebEngineLoadRequest loadRequest(url, QQuickWebEngineView::LoadSucceededStatus);
    Q_EMIT loadingChanged(&loadRequest);
    return;
}

void QQuickWebEngineErrorPage::loadStarted(const QUrl &provisionalUrl)
{
    QQuickWebEngineLoadRequest loadRequest(provisionalUrl, QQuickWebEngineView::LoadStartedStatus);
    Q_EMIT loadingChanged(&loadRequest);
}

QQuickWebEngineTestSupport::QQuickWebEngineTestSupport()
    : m_errorPage(new QQuickWebEngineErrorPage())
{
}

QQuickWebEngineErrorPage *QQuickWebEngineTestSupport::errorPage() const
{
    return m_errorPage.data();
}

void QQuickWebEngineTestSupport::testDialog(QSharedPointer<JavaScriptDialogController> dialogController)
{
    Q_ASSERT(!dialogController.isNull());

    QQuickWebEngineJavaScriptDialog dialog(dialogController);
    switch (dialogController->type()) {
    case WebContentsAdapterClient::AlertDialog:
        Q_EMIT alertDialog(&dialog);
        break;
    case WebContentsAdapterClient::ConfirmDialog:
        Q_EMIT confirmDialog(&dialog);
        break;
    case WebContentsAdapterClient::PromptDialog:
        Q_EMIT promptDialog(&dialog);
        break;
    case WebContentsAdapterClient::InternalAuthorizationDialog:
        break;
    default:
        Q_UNREACHABLE();
    }
}

QT_END_NAMESPACE

#include "moc_qquickwebenginetestsupport_p.cpp"