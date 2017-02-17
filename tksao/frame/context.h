// Copyright (C) 1999-2016
// Smithsonian Astrophysical Observatory, Cambridge, MA, USA
// For conditions of distribution and use, see copyright notice in "copyright"

#ifndef __context_h__
#define __context_h__

#include <pthread.h>

#include "base.h"
#include "colorscale.h"
#include "coord.h"
#include "frscale.h"
#include "list.h"
#include "fitsmask.h"
#include "fitsimage.h"
#include "head.h"

class FVContour;

class FitsZBound { 
 public:
  int zmin;
  int zmax;

 public:
  FitsZBound() {zmin= zmax=0;}
  FitsZBound(int z0, int z1) {zmin=z0; zmax=z1;}
  FitsZBound(const FitsZBound &bb) {zmin=bb.zmin; zmax=bb.zmax;}
  void set(int z0, int z1) {zmin=z0; zmax=z1;}
};
ostream& operator<<(ostream&, const FitsZBound&);

class Context {
 public:
  enum SmoothFunction {BOXCAR, TOPHAT, GAUSSIAN};

 protected:
  Base* parent_;

  FrScale frScale;

  int shareWCS_;

  int manageAxes_;
  int axesOrder_;

  int baxis_[FTY_MAXAXES]; // the first two are ignored
  int* naxis_; // the first two are ignored
  int slice_[FTY_MAXAXES]; // the first two are ignored

  int mosaicCount_;
  Base::MosaicType mosaicType;
  Coord::CoordSystem mosaicSystem;

  FitsHist::Function binFunction_;
  Vector binFactor_;
  int binBufferSize_;
  int binDepth_;

  Vector blockFactor_;

  int doSmooth_;
  SmoothFunction smoothFunction_;
  int smoothRadius_;

  FitsZBound iparams; // image bbox
  FitsZBound cparams; // crop bbox

  FVContour fvcontour_;
  List<ContourLevel> auxcontours_;
  int hasContour_;
  int hasAuxContour_;

 protected:
  void binFinish();
  int blockMask();
  int nhdu();
  void loadFinishMask();
  void loadFinishMosaic(FitsImage*);
  int loadFinishMosaicMask();
  int processMosaicKeywords(FitsImage*);
  void updateClip(FrScale*);
  void updateClipGlobal(FrScale*);
  void updateClipLocal(FrScale*);

  void contourList(ostream&, Coord::CoordSystem, Coord::SkyFrame, 
		   List<ContourLevel>&);

  void reorderAxis(char*, char**, int, int, int, size_t);
  void reorderThread(void*, char*, void* (void*), int*);

  pthread_t* thread_;

 public:
  FitsImage* bfits_;
  FitsImage* fits;
  FitsImage* cfits;

  List <FitsMask> mask;

 public:
  Context();
  ~Context();

  FVContour& fvcontour() {return fvcontour_;}
  List<ContourLevel>& auxcontours() {return auxcontours_;}

  void analysis();
  int axesOrder() {return axesOrder_;}

  Matrix bin(const Vector&);
  Matrix binCenter();
  Matrix binCursor();

  int block();
  void bltHist(char*, char*, int);

  int calcSlice();
  void contourAppendAux(ContourLevel*);
  void contourCreateFV(const char* color, int width, int dash,
		       FVContour::Method method, int numlevel, 
		       int smooth, 
		       FrScale::ColorScaleType colorScaleType,
		       float expo,
		       float clipMode, Vector limits, 
		       const char* level);
  void contourDeleteFV();
  void contourDeleteAux();
  void contourListFV(ostream&, Coord::CoordSystem, Coord::SkyFrame);
  void contourListAux(ostream&, Coord::CoordSystem, Coord::SkyFrame);
  void contourLoadAux(istream&);
  void contourLoadAux(istream&, const char*, int, int);
  void contourLoadAux(istream&, Coord::CoordSystem, Coord::SkyFrame, 
		      const char*, int, int);
  void contourPS(Widget::PSColorSpace cs);
  void contourX11(Pixmap, Coord::InternalSystem, int, int);
#ifdef MAC_OSX_TK
  void contourMacOSX();
#endif
#ifdef __WIN32
  void contourWin32();
#endif

  void deleteFits(FitsImage*);

  int fitsCount();

  Vector getClip(FrScale::ClipMode, float);
  Vector getClip();
  FitsZBound* getDataParams(FrScale::SecMode);   // return bbox in IMAGE
  Vector getMinMax();

  int hasContour() {return hasContour_;}
  int hasContourAux() {return hasAuxContour_;}
  double* histequ() {return frScale.histequ(fits);}

  Coord::Orientation IRAFOrientation(Coord::Orientation oo) 
    {return parent_->IRAFOrientation(oo);}
  int isMosaic() {return mosaicCount_>1 ? 1 : 0;}
  int isCube() {return nhdu()>1 ? 1 : 0;}

  int load(Base::MemType, const char*, FitsImage*, Base::LayerType);
  int loadExtCube(Base::MemType, const char*, FitsImage*);
  int loadSlice(Base::MemType, const char*, FitsImage*);
  int loadMosaic(Base::MemType, const char*, FitsImage*, 
		 Base::LayerType, Base::MosaicType, Coord::CoordSystem);
  int loadMosaicImage(Base::MemType, const char*, FitsImage*, 
		      Base::LayerType, Base::MosaicType, Coord::CoordSystem);
  int loadMosaicWFPC2(Base::MemType, const char*, FitsImage*);
  void loadInit(int, Base::MosaicType, Coord::CoordSystem);
  int loadFinish();

  int naxis(int ii) {return naxis_[ii];}
  int naxes();
  int nthreads() {return parent_->nthreads_;}

  void parent(Base* pp) {parent_ = pp;}

  void reorderAxes();
  void reorderWCSi(FitsHead*, char*, int, char);
  void reorderWCSij(FitsHead*, char*, int, char);
  void resetSecMode();

  int slice(int ii) {return slice_[ii];}

  void setAxesOrder(int);
  void setBinFunction(FitsHist::Function f) {binFunction_ = f;}
  void setBinFactor(const Vector&);
  void setBinToFactor(const Vector&);
  void setBinBufferSize(int s) {binBufferSize_ = s;}
  void setBinDepth(int d) {binDepth_ = d < 1 ? 1 : d;}
  FitsHist::Function binFunction() {return binFunction_;}
  Vector binFactor() {return binFactor_;}
  int binBufferSize() {return binBufferSize_;}
  int binDepth() {return binDepth_;}

  Vector setBlockFactor(const Vector&);
  Vector setBlockToFactor(const Vector&);
  const Vector& blockFactor() {return blockFactor_;}

  void setCrop3dParams();
  void setCrop3dParams(int,int);
  void setCrop3dParams(double, double);

  void setIIS();
  void resetIIS();

  void setSmooth(int ss) {doSmooth_ =ss;}
  void setSmooth(int ss, SmoothFunction ff, int rr)
  {doSmooth_=ss; smoothFunction_=ff; smoothRadius_=rr;}
  int hasSmooth() {return doSmooth_;}
  SmoothFunction smoothFunction() {return smoothFunction_;}
  int smoothRadius() {return smoothRadius_;}

  int shareWCS() {return shareWCS_;}

  void unload();
  void updateBinFileNames();
  void clearHist();
  void updateClip();
  void updateContours();
  void updateContours(const Matrix&);
  void updateContoursScale();
  void updateSlice(int, int);

  int updateClipScope(FrScale::ClipScope);
  int updateClipMode(FrScale::ClipMode);
  int updateClipMode(float);
  int updateMinMax(FrScale::MinMaxMode, int);
  // backward compatibility backup
  int updateMinMaxMode(FrScale::MinMaxMode);
  // backward compatibility backup
  int updateMinMaxSample(int);
  int updateUser(float,float);
  int updateZscale(float, int, int);
  // backward compatibility backup
  int updateZscaleContrast(float);
  // backward compatibility backup
  int updateZscaleSample(int);
  // backward compatibility backup
  int updateZscaleLine(int);
  int updateDataSec(int);
  int updateExpo(double);

  FrScale::ColorScaleType colorScaleType() {return frScale.colorScaleType();}
  FrScale::ClipScope clipScope() {return frScale.clipScope();}
  FrScale::ClipMode clipMode() {return frScale.clipMode();}
  int datasec() {return frScale.datasec();}
  float expo() {return frScale.expo();}
  double low() {return frScale.low();}
  double high() {return frScale.high();}
  int minmaxSample() {return frScale.minmaxSample();}
  FrScale::MinMaxMode minmaxMode() {return frScale.minmaxMode();}
  FrScale::SecMode secMode() {return frScale.secMode();}
  float autoCutPer() {return frScale.autoCutPer();}
  float zContrast() {return frScale.zContrast();}
  int zSample() {return frScale.zSample();}
  int zLine() {return frScale.zLine();}
  Vector clipUser() {return Vector(frScale.ulow(), frScale.uhigh());}

  void setClipScope(FrScale::ClipScope ss) {frScale.setClipScope(ss);}
  void setColorScaleType(FrScale::ColorScaleType tt)
  {frScale.setColorScaleType(tt);}
  void setSecMode(FrScale::SecMode);

};

#endif
