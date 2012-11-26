/****************************************************************************
**
** Copyright (C) 2012 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the Qt Commercial Charts Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

//  W A R N I N G
//  -------------
//
// This file is not part of the QtCommercial Chart API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef ABSTRACTDOMAIN_H
#define ABSTRACTDOMAIN_H
#include "qchartglobal.h"
#include <QRectF>
#include <QSizeF>
#include <QDebug>

QTCOMMERCIALCHART_BEGIN_NAMESPACE

class QAbstractAxis;

class QTCOMMERCIALCHART_AUTOTEST_EXPORT AbstractDomain: public QObject
{
    Q_OBJECT
public:
    enum DomainType { UndefinedDomain, XYDomain, XLogYDomain, LogXYDomain, LogXLogYDomain };
public:
    explicit AbstractDomain(QObject *object = 0);
    virtual ~AbstractDomain();

    void setSize(const QSizeF& size);
    QSizeF size() const;

    virtual DomainType type() = 0;

    virtual void setRange(qreal minX, qreal maxX, qreal minY, qreal maxY) = 0;
    void setRangeX(qreal min, qreal max);
    void setRangeY(qreal min, qreal max);
    void setMinX(qreal min);
    void setMaxX(qreal max);
    void setMinY(qreal min);
    void setMaxY(qreal max);

    qreal minX() const { return m_minX; }
    qreal maxX() const { return m_maxX; }
    qreal minY() const { return m_minY; }
    qreal maxY() const { return m_maxY; }

    qreal spanX() const;
    qreal spanY() const;
    bool isEmpty() const;

    void blockRangeSignals(bool block);
    bool rangeSignalsBlocked() const { return m_signalsBlocked; }

    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator== (const AbstractDomain &domain1, const AbstractDomain &domain2);
    friend bool QTCOMMERCIALCHART_AUTOTEST_EXPORT operator!= (const AbstractDomain &domain1, const AbstractDomain &domain2);
    friend QDebug QTCOMMERCIALCHART_AUTOTEST_EXPORT operator<<(QDebug dbg, const AbstractDomain &domain);

    virtual void zoomIn(const QRectF &rect) = 0;
    virtual void zoomOut(const QRectF &rect) = 0;
    virtual void move(qreal dx, qreal dy) = 0;

    virtual QPointF calculateGeometryPoint(const QPointF &point) const = 0;
    virtual QPointF calculateDomainPoint(const QPointF &point) const = 0;
    virtual QVector<QPointF> calculateGeometryPoints(const QList<QPointF>& vector) const = 0;

    virtual bool attachAxis(QAbstractAxis* axis);
    virtual bool detachAxis(QAbstractAxis* axis);

    static void looseNiceNumbers(qreal &min, qreal &max, int &ticksCount);
    static qreal niceNumber(qreal x, bool ceiling);

Q_SIGNALS:
    void updated();
    void rangeHorizontalChanged(qreal min, qreal max);
    void rangeVerticalChanged(qreal min, qreal max);

public Q_SLOTS:
    void handleVerticalAxisRangeChanged(qreal min,qreal max);
    void handleHorizontalAxisRangeChanged(qreal min,qreal max);

protected:
    qreal m_minX;
    qreal m_maxX;
    qreal m_minY;
    qreal m_maxY;
    QSizeF m_size;
    bool m_signalsBlocked;
};

QTCOMMERCIALCHART_END_NAMESPACE

#endif // ABSTRACTDOMAIN_H
