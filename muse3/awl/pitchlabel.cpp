//=============================================================================
//  Awl
//  Audio Widget Library
//  $Id:$
//
//  Copyright (C) 1999-2011 by Werner Schweer and others
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; version 2 of
//  the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//=============================================================================

#include "pitchedit.h"
#include "pitchlabel.h"
#include "utils.h"

#include <QApplication>
#include <QStyle>

namespace Awl {

//---------------------------------------------------------
//   PitchLabel
//---------------------------------------------------------

PitchLabel::PitchLabel()
      {
      _pitchMode = true;
      _value = -1;
      setFrameStyle(WinPanel | Sunken);
      setLineWidth(2);
      setMidLineWidth(3);
      setValue(0);
      int fw = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
      setIndent(fw);
      }

//---------------------------------------------------------
//   setPitchMode
//---------------------------------------------------------

void PitchLabel::setPitchMode(bool val)
      {
      _pitchMode = val;
      }

//---------------------------------------------------------
//   sizeHint
//---------------------------------------------------------

QSize PitchLabel::sizeHint() const
      {
      QFontMetrics fm(font());
      int fw = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
      int h  = fm.height() + fw * 2;
//      int w = 2 + fm.width(QString("A#8")) +  fw * 4;
// Width() is obsolete. Qt >= 5.11 use horizontalAdvance().
#if QT_VERSION >= 0x050b00
      int w = 2 + fm.horizontalAdvance(QString("-9999")) + fw * 4;     // must display 14Bit controller values
#else
      int w = 2 + fm.width(QString("-9999")) + fw * 4;     // must display 14Bit controller values
#endif
      return QSize(w, h).expandedTo(QApplication::globalStrut());
      }

//---------------------------------------------------------
//   setValue
//---------------------------------------------------------

void PitchLabel::setValue(int val)
      {
      if (val == _value)
            return;
      _value = val;
      QString s;
      if (_pitchMode)
            s = pitch2string(_value);
      else
            s.setNum(_value);
      setText(s);
      }

//---------------------------------------------------------
//   setInt
//---------------------------------------------------------

void PitchLabel::setInt(int val)
      {
      if (_pitchMode)
            setPitchMode(false);
      setValue(val);
      }

//---------------------------------------------------------
//   setPitch
//---------------------------------------------------------

void PitchLabel::setPitch(int val)
      {
      if (!_pitchMode) {
            setPitchMode(true);
            }
      setValue(val);
      }
}

