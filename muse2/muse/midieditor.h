//=========================================================
//  MusE
//  Linux Music Editor
//    $Id: midieditor.h,v 1.3.2.2 2009/02/02 21:38:00 terminator356 Exp $
//  (C) Copyright 1999 Werner Schweer (ws@seh.de)
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
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
//
//=========================================================

#ifndef __MIDIEDITOR_H__
#define __MIDIEDITOR_H__

#include "type_defs.h"
#include "al/sig.h"
#include "cobject.h"
#include "rasterizer.h"


#include <set>

class QGridLayout;
class QWidget;


namespace MusECore {
class Part;
class PartList;
class WavePart;
class Xml;
class Pos;
class Rasterizer;
}

namespace MusEGui {
class CtrlEdit;
class EventCanvas;
class MTScale;
class ScrollScale;
//class WaveView;

//---------------------------------------------------------
//   MidiEditor
//---------------------------------------------------------

class MidiEditor : public TopWin  {   
      Q_OBJECT

      MusECore::PartList* _pl;
      std::set<int> _parts;
      int _curDrumInstrument;  // currently selected instrument if drum
                               // editor
   protected:
      MusEGui::ScrollScale* hscroll;
      MusEGui::ScrollScale* vscroll;
      MusEGui::MTScale* time;
      EventCanvas* canvas;
      //WaveView* wview;

      std::list<CtrlEdit*> ctrlEditList;
      //int _raster;
      MusECore::Rasterizer _rasterizer;
      QGridLayout* mainGrid;
      QWidget* mainw;
      virtual void readStatus(MusECore::Xml&);
      virtual void writeStatus(int, MusECore::Xml&) const;
      void writePartList(int, MusECore::Xml&) const;
      void genPartlist();

   private slots:
      void addNewParts(const std::map< MusECore::Part*, std::set<MusECore::Part*> >&);

   public slots:
      void songChanged(MusECore::SongChangedFlags_t type);
      void setCurDrumInstrument(int instr);
      void horizontalZoomIn();
      void horizontalZoomOut();

      virtual void updateHScrollRange() { };
   signals:
      void curDrumInstrumentChanged(int);

   public:
      MidiEditor(ToplevelType t, int, MusECore::PartList*,
         QWidget* parent = 0, const char* name = 0);
      ~MidiEditor();

      // REMOVE Tim. When conversion to all Pos is done.
//       int rasterStep(unsigned tick) const   { return AL::sigmap.rasterStep(tick, _raster); }  
//       unsigned rasterVal(unsigned v)  const { return AL::sigmap.raster(v, _raster);  }
//       unsigned rasterVal1(unsigned v) const { return AL::sigmap.raster1(v, _raster); }
//       unsigned rasterVal2(unsigned v) const { return AL::sigmap.raster2(v, _raster); }
//       
//       // Newer versions:
//       MusECore::Pos rasterStep(MusECore::Pos pos) const;  
//       MusECore::Pos rasterVal(MusECore::Pos pos)  const; 
//       MusECore::Pos rasterVal1(MusECore::Pos pos) const;
//       MusECore::Pos rasterVal2(MusECore::Pos pos) const;
//       MusECore::Pos rasterSnapUp(MusECore::Pos pos) const;
//       MusECore::Pos rasterSnapDown(MusECore::Pos pos) const;
//       MusECore::Pos rasterUpNoSnap(MusECore::Pos pos) const;
//       MusECore::Pos rasterDownNoSnap(MusECore::Pos pos) const;
//       
//       // REMOVE Tim. When conversion to all Pos is done.
//       int raster() const           { return _raster; }
//       void setRaster(int val)      { _raster = val; }
//       //MusECore::Pos raster() const;
//       //void setRaster(int val)      { _raster = val; }
      
      const MusECore::Rasterizer& rasterizer() const { return _rasterizer; }
      
      MusECore::PartList* parts()            { return _pl;  }
      int curDrumInstrument() const  { return _curDrumInstrument; }
      MusECore::Part* curCanvasPart();
      void setCurCanvasPart(MusECore::Part*); 
      void addPart(MusECore::Part*);
      };

} // namespace MusEGui

#endif
