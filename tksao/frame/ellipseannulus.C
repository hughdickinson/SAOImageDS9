// Copyright (C) 1999-2017
// Smithsonian Astrophysical Observatory, Cambridge, MA, USA
// For conditions of distribution and use, see copyright notice in "copyright"

#include <tk.h>

#include "ellipseannulus.h"
#include "fitsimage.h"

EllipseAnnulus::EllipseAnnulus(Base* p, const Vector& ctr, 
			       const Vector& r, 
			       double ang, 
			       const char* clr, int* dsh, 
			       int wth, const char* fnt, const char* txt, 
			       unsigned short prop, const char* cmt, 
			       const List<Tag>& tg, const List<CallBack>& cb)
  : BaseEllipse(p, ctr, ang, clr, dsh, wth, fnt, txt, prop, cmt, tg, cb)
{
  numAnnuli_ = 1;
  annuli_ = new Vector[1];

  annuli_[0] = r;

  strcpy(type_,"ellipseannulus");
  numHandle = 4;

  updateBBox();
}

EllipseAnnulus::EllipseAnnulus(Base* p, const Vector& ctr, 
			       const Vector& inner,const Vector& outer,int num,
			       double ang)
  : BaseEllipse(p, ctr, ang)
{
  numAnnuli_ = num+1;
  annuli_ = new Vector[numAnnuli_];

  for (int i=0; i<numAnnuli_; i++)
    annuli_[i] = ((outer-inner)/num)*i+inner;

  strcpy(type_, "ellipseannulus");
  numHandle = 4 + numAnnuli_;

  updateBBox();
}

EllipseAnnulus::EllipseAnnulus(Base* p, const Vector& ctr, 
			       const Vector& inner,const Vector& outer,int num,
			       double ang, 
			       const char* clr, int* dsh, 
			       int wth, const char* fnt, const char* txt, 
			       unsigned short prop, const char* cmt, 
			       const List<Tag>& tg, const List<CallBack>& cb)
  : BaseEllipse(p, ctr, ang, clr, dsh, wth, fnt, txt, prop, cmt, tg, cb)
{
  numAnnuli_ = num+1;
  annuli_ = new Vector[numAnnuli_];

  for (int i=0; i<numAnnuli_; i++)
    annuli_[i] = ((outer-inner)/num)*i+inner;

  strcpy(type_, "ellipseannulus");
  numHandle = 4 + numAnnuli_;

  updateBBox();
}

EllipseAnnulus::EllipseAnnulus(Base* p, const Vector& ctr, 
			       int an, Vector* r,
			       double ang, 
			       const char* clr, int* dsh, 
			       int wth, const char* fnt, const char* txt, 
			       unsigned short prop, const char* cmt, 
			       const List<Tag>& tg, const List<CallBack>& cb)
  : BaseEllipse(p, ctr, ang, clr, dsh, wth, fnt, txt, prop, cmt, tg, cb)
{
  numAnnuli_ = an;
  annuli_ = new Vector[numAnnuli_];

  for (int i=0; i<numAnnuli_; i++)
    annuli_[i] = r[i];
  sortAnnuli();

  strcpy(type_, "ellipseannulus");
  numHandle = 4 + numAnnuli_;

  updateBBox();
  doCallBack(CallBack::EDITCB);
}

EllipseAnnulus::EllipseAnnulus(const EllipseAnnulus& a) : BaseEllipse(a) {}

void EllipseAnnulus::edit(const Vector& v, int h)
{
  Matrix mm = bckMatrix();
  Vector n = v * mm;

  if (h<5) {
    // don't go thru the center
    if (n[0]!=0 && n[1]!=0) {
      Vector o = annuli_[numAnnuli_-1];
      for (int i=0; i<numAnnuli_; i++) {
	annuli_[i][0] *= fabs(n[0]/o[0]);
	annuli_[i][1] *= fabs(n[1]/o[1]);
      }
    }
  }
  else {
    // we must have some length
    double l = n.length();
    annuli_[h-5] = annuli_[numAnnuli_-1] * l/annuli_[numAnnuli_-1][0];
  }

  updateBBox();
  doCallBack(CallBack::EDITCB);
}

void EllipseAnnulus::editEnd()
{
  sortAnnuli();

  updateBBox();
  doCallBack(CallBack::EDITENDCB);
}

int EllipseAnnulus::addAnnuli(const Vector& v)
{
  Matrix mm = bckMatrix();
  double l = (v * mm).length();
  Vector rr = annuli_[numAnnuli_-1] * l/annuli_[numAnnuli_-1][0];

  return insertAnnuli(rr);
}

void EllipseAnnulus::analysis(AnalysisTask mm, int which)
{
  switch (mm) {
  case RADIAL:
    if (!analysisRadial_ && which) {
      addCallBack(CallBack::MOVECB, analysisRadialCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITCB, analysisRadialCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITENDCB, analysisRadialCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::ROTATECB, analysisRadialCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::UPDATECB, analysisRadialCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::DELETECB, analysisRadialCB_[1], 
		  parent->options->cmdName);
    }
    if (analysisRadial_ && !which) {
      deleteCallBack(CallBack::MOVECB, analysisRadialCB_[0]);
      deleteCallBack(CallBack::EDITCB, analysisRadialCB_[0]);
      deleteCallBack(CallBack::EDITENDCB, analysisRadialCB_[0]);
      deleteCallBack(CallBack::ROTATECB, analysisRadialCB_[0]);
      deleteCallBack(CallBack::UPDATECB, analysisRadialCB_[0]);
      deleteCallBack(CallBack::DELETECB, analysisRadialCB_[1]);
    }

    analysisRadial_ = which;
    break;
  case STATS:
    if (!analysisStats_ && which) {
      addCallBack(CallBack::MOVECB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITCB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::EDITENDCB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::ROTATECB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::UPDATECB, analysisStatsCB_[0], 
		  parent->options->cmdName);
      addCallBack(CallBack::DELETECB, analysisStatsCB_[1], 
		  parent->options->cmdName);
    }
    if (analysisStats_ && !which) {
      deleteCallBack(CallBack::MOVECB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::EDITCB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::EDITENDCB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::ROTATECB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::UPDATECB, analysisStatsCB_[0]);
      deleteCallBack(CallBack::DELETECB, analysisStatsCB_[1]);
    }

    analysisStats_ = which;
    break;
  default:
    // na
    break;
  }
}

void EllipseAnnulus::analysisRadial(char* xname, char* yname, char* ename,
				    Coord::CoordSystem sys)
{
  double* xx;
  double* yy;
  double* ee;

  BBox* bb = new BBox[numAnnuli_];
  Matrix mm = Rotate(angle) * Translate(center);

  for (int ii=0; ii<numAnnuli_; ii++) {
    Vector vv = annuli_[ii];
    bb[ii] = BBox(-vv * mm);
    bb[ii].bound( vv * mm);
    bb[ii].bound(Vector( vv[0],-vv[1]) * mm);
    bb[ii].bound(Vector(-vv[0], vv[1]) * mm);
  }

  int num = parent->markerAnalysisRadial(this, &xx, &yy, &ee,
					 numAnnuli_-1, annuli_, 
					 bb, sys);
  analysisXYEResult(xname, yname, ename, xx, yy, ee, num);
}

void EllipseAnnulus::analysisStats(Coord::CoordSystem sys, Coord::SkyFrame sky)
{
  ostringstream str;
  BBox* bb = new BBox[numAnnuli_];
  Matrix mm = Rotate(angle) * Translate(center);

  for (int ii=0; ii<numAnnuli_; ii++) {
    Vector vv = annuli_[ii];
    bb[ii] = BBox(-vv * mm);
    bb[ii].bound( vv * mm);
    bb[ii].bound(Vector( vv[0],-vv[1]) * mm);
    bb[ii].bound(Vector(-vv[0], vv[1]) * mm);
  }

  parent->markerAnalysisStats(this, str, numAnnuli_-1, bb, sys, sky);
  str << ends;
  Tcl_AppendResult(parent->interp, str.str().c_str(), NULL);
}

// list

void EllipseAnnulus::list(ostream& str, Coord::CoordSystem sys, 
			  Coord::SkyFrame sky, Coord::SkyFormat format,
			  int conj, int strip)
{
  FitsImage* ptr = parent->findFits(sys,center);
  listPre(str, sys, sky, ptr, strip, 0);

  switch (sys) {
  case Coord::IMAGE:
  case Coord::PHYSICAL:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    listNonCel(ptr, str, sys);
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      double aa = parent->mapAngleFromRef(angle,sys,sky);
      switch (format) {
      case Coord::DEGREES:
	{
	  Vector vv = ptr->mapFromRef(center,sys,sky);
	  str << "ellipse(" << setprecision(10) << vv
	      << setprecision(3) << fixed;
	  for (int ii=0; ii<numAnnuli_; ii++) {
	    Vector rr = ptr->mapLenFromRef(annuli_[ii],sys,Coord::ARCSEC);
	    str << ',' << setunit('"') << rr;
	  }
	  str.unsetf(ios_base::floatfield);
	  str << setprecision(8) << ',' << radToDeg(aa) << ')';
	}
	break;
      case Coord::SEXAGESIMAL:
	listRADEC(ptr,center,sys,sky,format);
	str << "ellipse(" << ra << ',' << dec
	    << setprecision(3) << fixed;
	for (int ii=0; ii<numAnnuli_; ii++) {
	  Vector rr = ptr->mapLenFromRef(annuli_[ii],sys,Coord::ARCSEC);
	  str << ',' << setunit('"') << rr;
	}
	str.unsetf(ios_base::floatfield);
	str << setprecision(8) << ',' << radToDeg(aa) << ')';
	break;
      }
    }
    else
      listNonCel(ptr, str, sys);
  }

  listPost(str, conj, strip);
}

void EllipseAnnulus::listNonCel(FitsImage* ptr, ostream& str, 
				Coord::CoordSystem sys)
{
  Vector vv = ptr->mapFromRef(center,sys);
  double aa = parent->mapAngleFromRef(angle,sys);
  str << "ellipse(" << setprecision(8) << vv;
  for (int ii=0; ii<numAnnuli_; ii++) {
    Vector rr = ptr->mapLenFromRef(annuli_[ii],sys);
    str << ',' << rr;
  }
  str << ',' << radToDeg(aa) << ')';
}

void EllipseAnnulus::listXML(ostream& str, Coord::CoordSystem sys, 
			     Coord::SkyFrame sky, Coord::SkyFormat format)
{
  FitsImage* ptr = parent->findFits(sys,center);

  XMLRowInit();
  XMLRow(XMLSHAPE,type_);

  XMLRowCenter(ptr,sys,sky,format);
  XMLRowRadius(ptr,sys,annuli_,numAnnuli_);
  XMLRowAng(sys,sky);

  XMLRowProps(ptr,sys);
  XMLRowEnd(str);
}

void EllipseAnnulus::listPros(ostream& str, Coord::CoordSystem sys, 
			      Coord::SkyFrame sky, Coord::SkyFormat format,
			      int strip)
{
  FitsImage* ptr = parent->findFits();

  switch (sys) {
  case Coord::IMAGE:
  case Coord::DETECTOR:
  case Coord::AMPLIFIER:
    sys = Coord::IMAGE;
  case Coord::PHYSICAL:
    {
      Vector vv = ptr->mapFromRef(center,sys);
      for (int ii=0; ii<numAnnuli_; ii++) {
	coord.listProsCoordSystem(str,sys,sky);
	str << "; ";

	Vector rr = ptr->mapLenFromRef(annuli_[ii],Coord::IMAGE);
        str << "ellipse " << setprecision(8) << vv << ' ' << rr << ' '
            << radToDeg(angle);

	if (ii!=0) {
	  Vector r1 = ptr->mapLenFromRef(annuli_[ii-1],Coord::IMAGE);
          str << " & !ellipse " << setprecision(8) << vv << ' ' << r1 << ' '
              << radToDeg(angle);
	}

	listProsPost(str, strip);
      }
    }
    break;
  default:
    if (ptr->hasWCSCel(sys)) {
      switch (format) {
      case Coord::DEGREES:
	{
	  Vector vv = ptr->mapFromRef(center,sys,sky);
	  for (int ii=0; ii<numAnnuli_; ii++) {
	    coord.listProsCoordSystem(str,sys,sky);
	    str << "; ";

	    Vector rr = ptr->mapLenFromRef(annuli_[ii],sys,Coord::ARCSEC);
            str << "ellipse "
                << setprecision(10) << setunit('d') << vv << ' '
                << setprecision(3) << setunit('"') << fixed << rr << ' ';
	    str.unsetf(ios_base::floatfield);
	    str << setprecision(8) << radToDeg(angle);

	    if (ii!=0) {
	      Vector r1 = ptr->mapLenFromRef(annuli_[ii-1],sys,Coord::ARCSEC);
              str << " & !ellipse "
                  << setprecision(8) << setunit('d') << vv << ' '
                  << setprecision(3) << setunit('"') << fixed << r1 << ' ';
              str.unsetf(ios_base::floatfield);
              str << setprecision(8) << radToDeg(angle);
	    }

	    listProsPost(str, strip);
	  }
	}
	break;
      case Coord::SEXAGESIMAL:
	listRADECPros(ptr,center,sys,sky,format);
	for (int ii=0; ii<numAnnuli_; ii++) {
	  coord.listProsCoordSystem(str,sys,sky);
	  str << "; ";

	  Vector rr = ptr->mapLenFromRef(annuli_[ii],sys,Coord::ARCSEC);
          str << "ellipse " << ra << ' ' << dec << ' '
              << setprecision(3) << setunit('"') << fixed << rr << ' ';
          str.unsetf(ios_base::floatfield);
          str << setprecision(8) << radToDeg(angle);

	  if (ii!=0) {
	    Vector r1 = ptr->mapLenFromRef(annuli_[ii-1],sys,Coord::ARCSEC);
            str << " & !ellipse " << ra << ' ' << dec << ' '
                << setprecision(3) << setunit('"') << fixed << r1 << ' ';
            str.unsetf(ios_base::floatfield);
            str << setprecision(8) << radToDeg(angle);
	  }

	  listProsPost(str, strip);
	}
	break;
      }
    }
  }
}

void EllipseAnnulus::listSAOimage(ostream& str, int strip)
{
  FitsImage* ptr = parent->findFits();
  listSAOimagePre(str);

  for (int ii=0; ii<numAnnuli_; ii++) {
    Vector vv = ptr->mapFromRef(center,Coord::IMAGE);
    str << "ellipse(" << setprecision(8) << vv << ','
        << annuli_[ii] << ',' << radToDeg(angle) << ')';

    if (ii!=0)
      str << " & !ellipse(" << setprecision(8) << vv << ','
          << annuli_[ii-1] << ',' << radToDeg(angle) << ')';

    listSAOimagePost(str, strip);
  }
}


