/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QWEBENGINECERTIFICATEERROR_H
#define QWEBENGINECERTIFICATEERROR_H

#include <QtWebEngineWidgets/qtwebenginewidgetsglobal.h>

#include <QtCore/qsharedpointer.h>
#include <QtCore/qurl.h>
#include <QtNetwork/QSslCertificate>

QT_BEGIN_NAMESPACE

class CertificateErrorController;
class QWebEngineCertificateErrorPrivate;

class QWEBENGINEWIDGETS_EXPORT QWebEngineCertificateError {
public:
    QWebEngineCertificateError(int error, QUrl url, bool overridable, QString errorDescription);
    ~QWebEngineCertificateError();

    // Keep this identical to CertificateErrorController::CertificateError, or add mapping layer.
    enum Error {
        SslPinnedKeyNotInCertificateChain = -150,
        CertificateCommonNameInvalid = -200,
        CertificateDateInvalid = -201,
        CertificateAuthorityInvalid = -202,
        CertificateContainsErrors = -203,
        CertificateNoRevocationMechanism = -204,
        CertificateUnableToCheckRevocation = -205,
        CertificateRevoked = -206,
        CertificateInvalid = -207,
        CertificateWeakSignatureAlgorithm = -208,
        CertificateNonUniqueName = -210,
        CertificateWeakKey = -211,
        CertificateNameConstraintViolation = -212,
        CertificateValidityTooLong = -213,
        CertificateTransparencyRequired = -214,
    };

    Error error() const;
    QUrl url() const;
    bool isOverridable() const;
    QString errorDescription() const;

    QWebEngineCertificateError(const QWebEngineCertificateError &other);
    QWebEngineCertificateError& operator=(const QWebEngineCertificateError &other);

    void defer();
    bool deferred() const;

    void rejectCertificate();
    void ignoreCertificateError();
    bool answered() const;

    QList<QSslCertificate> chain() const;

private:
    friend class QWebEnginePagePrivate;
    QWebEngineCertificateError(const QSharedPointer<CertificateErrorController> &controller);
    QExplicitlySharedDataPointer<QWebEngineCertificateErrorPrivate> d;
};

QT_END_NAMESPACE

#endif // QWEBENGINECERTIFICATEERROR_H
