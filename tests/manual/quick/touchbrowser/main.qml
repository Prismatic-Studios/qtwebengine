/****************************************************************************
**
** Copyright (C) 2018 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtQuick.Layouts
import QtWebEngine

Item {
    function load(url) {
        webEngineView.url = url;
    }

    ColumnLayout {
        anchors.fill: parent

        AddressBar {
            id: addressBar

            Layout.fillWidth: true
            Layout.margins: 5
            height: 25

            color: "white"
            radius: 4

            progress: webEngineView && webEngineView.loadProgress
            iconUrl: webEngineView && webEngineView.icon
            pageUrl: webEngineView && webEngineView.url

            onAccepted: webEngineView.url = addressUrl
        }

        WebEngineView {
            id: webEngineView

            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}
