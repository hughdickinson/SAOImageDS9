%{

global yy
set yy(x) 0
set yy(y) 0
set yy(format) degrees
set yy(w) 0
set yy(h) 0
set yy(rformat) degrees

global file
set file(type) fits
set file(mode) {}
set file(layer) {}
set file(mosaic) wcs
set file(load) 0

global cvarname
set cvarname {}

%}

%token INT_
%token REAL_
%token STRING_
%token SEXSTR_
%token HMSSTR_
%token DMSSTR_

%token 2MASSCMD_
%token 3DCMD_
%token ALIGNCMD_
%token ASINHCMD_
%token BINCMD_
%token BGCMD_
%token BLOCKCMD_
%token BLUECMD_
%token BLINKCMD_
%token CATALOGCMD_
%token CDCMD_
%token CMAPCMD_
%token CONSOLECMD_
%token CROPCMD_
%token CROSSHAIRCMD_
%token CUBECMD_
%token CURSORCMD_
%token GREENCMD_
%token FITSCMD_
%token FRAMECMD_
%token HEIGHTCMD_
%token HELPCMD_
%token HISTEQUCMD_
%token ICONIFYCMD_
%token INVERTCMD_
%token IRAFALIGNCMD_
%token LINEARCMD_
%token LOGCMD_
%token LOWERCMD_
%token MINMAXCMD_
%token MODECMD_
%token NANCMD_
%token ORIENTCMD_
%token PANCMD_
%token PREFSCMD_
%token PIXELTABLECMD_
%token PRIVATECMD_
%token POWCMD_
%token QUITCMD_
%token RAISECMD_
%token REDCMD_
%token RGBCMD_
%token ROTATECMD_
%token SCALECMD_
%token SINGLECMD_
%token SINHCMD_
%token SLEEPCMD_
%token SOURCECMD_
%token SQUAREDCMD_
%token SQRTCMD_
%token THEMECMD_
%token THREADSCMD_
%token TILECMD_
%token WCSCMD_
%token WIDTHCMD_
%token ZMAXCMD_
%token ZOOMCMD_
%token ZSCALECMD_

%token 123_
%token 132_
%token 213_
%token 231_
%token 312_
%token 321_

%token 1AND2_
%token 1NOT2_
%token 2NOT1_
%token 3D_
%token ABOUT_
%token ADD_
%token AIP_
%token ALIGN_
%token ALL_
%token ALLCOLS_
%token ALLROWS_
%token AMPLIFIER_
%token ANGLE_
%token APPEND_
%token ARCMIN_
%token ARCSEC_
%token ARROW_
%token ASINH_
%token AUTO_
%token AUTOMATIC_
%token AVERAGE_
%token AXES_
%token AXIS_
%token AZ_
%token B1950_
%token BACK_
%token BG_
%token BGCOLOR_
%token BIN_
%token BLOCK_
%token BLUE_
%token BOLD_
%token BORDER_
%token BOX_
%token BOXCIRCLE_
%token BROADCAST_
%token BUFFERSIZE_
%token CANCEL_
%token CATALOG_
%token CENTER_
%token CDS_
%token CHANNEL_
%token CIRCLE_
%token CLEAR_
%token CLOSE_
%token COLOR_
%token COLORBAR_
%token COLORMAP_
%token COLS_
%token COLUMN_
%token COLSZ_
%token COMPASS_
%token CONDITION_
%token CONTRAST_
%token COORD_
%token COORDINATE_
%token COURIER_
%token CROP_
%token CROSS_
%token CROSSHAIR_
%token CSV_
%token CURRENT_
%token DATAMIN_
%token DATASEC_
%token DEC_
%token DECR_
%token DEGREES_
%token DEPTH_
%token DETECTOR_
%token DELETE_
%token DIAMOND_
%token DIRECTION_
%token ECLIPTIC_
%token EDIT_
%token EL_
%token ELLIPSE_
%token ERROR_
%token EXAMINE_
%token EXP_
%token EXPORT_
%token FACTOR_
%token FALSE_
%token FILE_
%token FILTER_
%token FIRST_
%token FIT_
%token FK4_
%token FK5_
%token FONT_
%token FONTSIZE_
%token FONTSLANT_
%token FONTWEIGHT_
%token FORMAT_
%token FORWARD_
%token FRAME_
%token FRAMENO_
%token FUNCTION_
%token GALACTIC_
%token GAP_
%token GLOBAL_
%token GREEN_
%token GRID_
%token HEADER_
%token HELVETICA_
%token HIDE_
%token HIGHLITE_
%token HISTEQU_
%token ICRS_
%token IMAGE_
%token IMPORT_
%token IN_
%token INCR_
%token INTERVAL_
%token INVERT_
%token IRAF_
%token IRAFALIGN_
%token IRAFMIN_
%token ITALIC_
%token J2000_
%token LAST_
%token LAYOUT_
%token LIMITS_
%token LINE_
%token LINEAR_
%token LOAD_
%token LOCAL_
%token LOCATION_
%token LOCK_
%token LOG_
%token MANUAL_
%token MATCH_
%token MAXROWS_
%token MECUBE_
%token METHOD_
%token MINMAX_
%token MIP_
%token MODE_
%token MOSAIC_
%token MOSAICIMAGE_
%token MOVE_
%token MULTIFRAME_
%token NAME_
%token NANCOLOR_
%token NEW_
%token NEXT_
%token NO_
%token NONE_
%token NORMAL_
%token OFF_
%token ON_
%token OPEN_
%token ORDER_
%token OUT_
%token PAN_
%token PANTO_
%token PHYSICAL_
%token PLAY_
%token PLOT_
%token POINT_
%token POINTER_
%token POW_
%token PREV_
%token PRINT_
%token PSKY_
%token PSYSTEM_
%token RA_
%token RED_
%token REFRESH_
%token REGION_
%token REGIONS_
%token REMOVE_
%token REPLACE_
%token RESET_
%token RETRIEVE_
%token RETURN_
%token RGB_
%token RGBCUBE_
%token RGBIMAGE_
%token ROMAN_
%token ROTATE_
%token ROW_
%token SAMP_
%token SAMPLE_
%token SAVE_
%token SB_
%token SCALE_
%token SCALELIMITS_
%token SCAN_
%token SCOPE_
%token SEND_
%token SERVER_
%token SEXAGESIMAL_
%token SHAPE_
%token SHOW_
%token SINH_
%token SIZE_
%token SIZE2_
%token SKY_
%token SKYFORMAT_
%token SLICE_
%token SMOOTH_
%token SQUARED_
%token SQRT_
%token SORT_
%token STARBASE_
%token STOP_
%token SUM_
%token SURVEY_
%token SYMBOL_
%token SYSTEM_
%token TAG_
%token THREADS_
%token TIMES_
%token TEXT_
%token TO_
%token TRUE_
%token TSV_
%token UNIQUE_
%token UNITS_
%token UPDATE_
%token USER_
%token VALUE_
%token VIEW_
%token VOT_
%token VP_
%token WCS_
%token WCSA_
%token WCSB_
%token WCSC_
%token WCSD_
%token WCSE_
%token WCSF_
%token WCSG_
%token WCSH_
%token WCSI_
%token WCSJ_
%token WCSK_
%token WCSL_
%token WCSM_
%token WCSN_
%token WCSO_
%token WCSP_
%token WCSQ_
%token WCSR_
%token WCSS_
%token WCST_
%token WCSU_
%token WCSV_
%token WCSW_
%token WCSX_
%token WCSY_
%token WCSZ_
%token WFPC2_
%token XML_
%token XY_
%token YES_
%token ZMAX_
%token ZOOM_
%token ZSCALE_

%%

commands : commands command
 | command
 ;

int : INT_ {set _ $1}
 | 123_ {set _ 123}
 | 132_ {set _ 132}
 | 213_ {set _ 213}
 | 231_ {set _ 231}
 | 312_ {set _ 312}
 | 321_ {set _ 321}
 ;

command : 2MASSCMD_ {2MASSDialog} 2mass
 | 3DCMD_ {3DDialog} 3d
 | ALIGNCMD_ align
 | ASINHCMD_ {global scale; set scale(type) asinh; ChangeScale}
 | BINCMD_ bin
 | BGCMD_ STRING_ {global pds9; set pds9(bg) $2; PrefsBgColor}
 | BLINKCMD_ blink
 | BLOCKCMD_ {ProcessRealizeDS9} block
 | BLUECMD_ {global current; set current(rgb) blue; RGBChannel}
 | CATALOGCMD_ {CatalogInitCmd} catalog
 | CDCMD_ cd
 | CMAPCMD_ {ProcessRealizeDS9} cmap
 | CONSOLECMD_ {global ds9; OpenConsole; InitError $ds9(msg,src)}
 | CROPCMD_ {ProcessRealizeDS9} crop
 | CROSSHAIRCMD_ {ProcessRealizeDS9} crosshair
 | CUBECMD_ {CubeDialog} cube
 | CURSORCMD_ int int {CursorCmd $2 $3}
 | FITSCMD_ fits
 | FRAMECMD_ frame
 | GREENCMD_ {global current; set current(rgb) green; RGBChannel}
 | HEIGHTCMD_ int {global canvas; RealizeDS9; set canvas(height) $2; UpdateView}
 | HELPCMD_ {HelpCommand}
 | HISTEQUCMD_ {global scale; set scale(type) histequ; ChangeScale}
 | ICONIFYCMD_ iconify
 | INVERTCMD_ {global colorbar; set colorbar(invert) 1; InvertColorbar}
 # backward compatibility
 | IRAFALIGNCMD_ yesno {global pds9; set pds9(iraf) $2; PrefsIRAFAlign}
 | LINEARCMD_ {global scale; set scale(type) linear; ChangeScale}
 | LOGCMD_ {global scale; set scale(type) log; ChangeScale}
 | LOWERCMD_ {global ds9; lower $ds9(top)}
 | MINMAXCMD_ minmax
 | MODECMD_ mode
 | NANCMD_ STRING_ {global pds9; set pds9(nan) $2; PrefsNanColor}
 | ORIENTCMD_ {ProcessRealizeDS9} orient
 | PANCMD_ {ProcessRealizeDS9} pan
 | PIXELTABLECMD_ pixelTable
 | PREFSCMD_ prefs
 # backward compatibility
 | PRIVATECMD_ 
 | POWCMD_ {global scale; set scale(type) pow; ChangeScale}
 | QUITCMD_ {QuitDS9}
 | RAISECMD_ {global ds9; raise $ds9(top)}
 | REDCMD_ {global current; set current(rgb) red; RGBChannel}
 | RGBCMD_ {RGBDialog} rgb
 | ROTATECMD_ {ProcessRealizeDS9} rotate
 | SINGLECMD_ {global current; ProcessRealizeDS9; set current(display) single; DisplayMode}
 | SINHCMD_ {global scale; set scale(type) sinh; ChangeScale}
 | SLEEPCMD_ {UpdateDS9; RealizeDS9} sleep
 | SOURCECMD_ STRING_ {SourceCmd $2}
 | SQUAREDCMD_ {global scale; set scale(type) squared; ChangeScale}
 | SQRTCMD_ {global scale; set scale(type) sqrt; ChangeScale}
 | SCALECMD_ scale
 # backward compatibility
 | THEMECMD_
 | THREADSCMD_ int {global ds9; set ds9(threads) $2; ChangeThreads}
 | TILECMD_ tile
 | WCSCMD_ wcs
 | WIDTHCMD_ int {global canvas; RealizeDS9; set canvas(width) $2; UpdateView}
 | ZMAXCMD_ {global scale; set scale(mode) zmax; ChangeScaleMode}
 | ZOOMCMD_ {ProcessRealizeDS9} zoom
 | ZSCALECMD_ zscale
 | STRING_ {CommandLineFileName $1}
 ;

numeric	: int {set _ $1}
 | REAL_ {set _ $1}
 ;

yes : YES_ {set _ 1}
 | TRUE_ {set _ 1}
 | ON_ {set _ 1}
# | '1' {set _ 1}
 ;

no : NO_ {set _ 0}
 | FALSE_ {set _ 0}
 | OFF_ {set _ 0}
# | 0_ {set _ 0}
 ;

yesno : YES_ {set _ 1}
 | TRUE_ {set _ 1}
 | ON_ {set _ 1}
# | '1' {set _ 1}
 | NO_ {set _ 0}
 | FALSE_ {set _ 0}
 | OFF_ {set _ 0}
# | '0' {set _ 0}
 ;

font : TIMES_ {set _ times}
 | HELVETICA_ {set _ helvetica}
 | COURIER_ {set _ courier}
 ;

fontweight : NORMAL_ {set _ normal}
 | BOLD_ {set _ bold}
 ;

fontslant : ROMAN_ {set _ roman}
 | ITALIC_ {set _ italic}
 ;

skycoord : numeric numeric {global yy; set yy(x) $1; set yy(y) $2}
 | SEXSTR_ SEXSTR_ {global yy; set yy(x) $1; set yy(y) $2}
 ;

skycoordformat : numeric numeric {global yy; set yy(x) $1; set yy(y) $2; set yy(format) degrees}
 | numeric numeric DEGREES_ {global yy; set yy(x) $1; set yy(y) $2; set yy(format) degrees}
 | SEXSTR_ SEXSTR_ {global yy; set yy(x) $1; set yy(y) $2; set yy(format) sexagesimal}
 | SEXSTR_ SEXSTR_ SEXAGESIMAL_ {global yy; set yy(x) $1; set yy(y) $2; set yy(format) sexagesimal}
 ;

skysize : numeric numeric {global yy; set yy(w) $1; set yy(h) $2; set yy(rformat) degrees}
 | numeric numeric skydist {global yy; set yy(w) $1; set yy(h) $2; set yy(rformat) $3}
 ;

skyframe : FK4_ {set _ fk4}
 | B1950_ {set _ fk4}
 | FK5_ {set _ fk5}
 | J2000_ {set _ fk5}
 | ICRS_ {set _ icrs}
 | GALACTIC_ {set _ galactic}
 | ECLIPTIC_ {set _ ecliptic}
 ;

skyformat : DEGREES_ {set _ degrees}
 | SEXAGESIMAL_ {set _ sexagesimal}
 ;

skydist : DEGREES_ {set _ degrees}
 | ARCMIN_ {set _ arcmin}
 | ARCSEC_ {set _ arcsec}
 ;

coordsys : IMAGE_ {set _ image}
 | PHYSICAL_ {set _ physical}
 | AMPLIFIER_ {set _ amplifier}
 | DETECTOR_ {set _ detector}
 | wcssys {set _ $1}
 ;

wcssys : WCS_ {set _ wcs}
 | WCSA_ {set _ wcsa}
 | WCSB_ {set _ wcsb}
 | WCSC_ {set _ wcsc}
 | WCSD_ {set _ wcsd}
 | WCSE_ {set _ wcse}
 | WCSF_ {set _ wcsf}
 | WCSG_ {set _ wcsg}
 | WCSH_ {set _ wcsh}
 | WCSI_ {set _ wcsi}
 | WCSJ_ {set _ wcsj}
 | WCSK_ {set _ wcsk}
 | WCSL_ {set _ wcsl}
 | WCSM_ {set _ wcsm}
 | WCSN_ {set _ wcsn}
 | WCSO_ {set _ wcso}
 | WCSP_ {set _ wcsp}
 | WCSQ_ {set _ wcsq}
 | WCSR_ {set _ wcsr}
 | WCSS_ {set _ wcss}
 | WCST_ {set _ wcst}
 | WCSU_ {set _ wcsu}
 | WCSV_ {set _ wcsv}
 | WCSW_ {set _ wcsw}
 | WCSX_ {set _ wcsx}
 | WCSY_ {set _ wcsy}
 | WCSZ_ {set _ wcsz}
 ;

mosaicImageType : mosaicType {set _ $1}
 | WFPC2_ {set _ wfpc2}
 ;

mosaicType : IRAF_ {set _ iraf}
 | WCS_ {set _ wcs}
 | WCSA_ {set _ wcsa}
 | WCSB_ {set _ wcsb}
 | WCSC_ {set _ wcsc}
 | WCSD_ {set _ wcsd}
 | WCSE_ {set _ wcse}
 | WCSF_ {set _ wcsf}
 | WCSG_ {set _ wcsg}
 | WCSH_ {set _ wcsh}
 | WCSI_ {set _ wcsi}
 | WCSJ_ {set _ wcsj}
 | WCSK_ {set _ wcsk}
 | WCSL_ {set _ wcsl}
 | WCSM_ {set _ wcsm}
 | WCSN_ {set _ wcsn}
 | WCSO_ {set _ wcso}
 | WCSP_ {set _ wcsp}
 | WCSQ_ {set _ wcsq}
 | WCSR_ {set _ wcsr}
 | WCSS_ {set _ wcss}
 | WCST_ {set _ wcst}
 | WCSU_ {set _ wcsu}
 | WCSV_ {set _ wcsv}
 | WCSW_ {set _ wcsw}
 | WCSX_ {set _ wcsx}
 | WCSY_ {set _ wcsy}
 | WCSZ_ {set _ wcsz}
 ;

2mass : {IMGSVRApply dtwomass 1}
 | STRING_ {global dtwomass; set dtwomass(name) $1; IMGSVRApply dtwomass 1}
 | NAME_ STRING_ {global dtwomass; set dtwomass(name) $2; IMGSVRApply dtwomass 1}
 | COORD_ skycoordformat {global yy; global dtwomass; set dtwomass(x) $yy(x); set dtwomass(y) $yy(y); set dtwomass(skyformat) $yy(format); set dtwomass(skyformat,msg) $yy(format); IMGSVRApply dtwomass 1}
 | SIZE_ skysize {global yy; global dtwomass; set dtwomass(width) $yy(w); set dtwomass(height) $yy(h); set dtwomass(rformat) $yy(rformat); set dtwomass(rformat,msg) $yy(rformat)}
 | SAVE_ yesno {global dtwomass; set dtwomass(save) $2}
 | FRAME_ 2massFrame {global dtwomass; set dtwomass(mode) $2}
 | UPDATE_ FRAME_ {IMGSVRUpdate dtwomass; IMGSVRApply dtwomass 1}
 | UPDATE_ CROSSHAIR_ {IMGSVRCrosshair dtwomass; IMGSVRApply dtwomass 1}
 | SURVEY_ 2massSurvey {global dtwomass; set dtwomass(survey) $2}
 | OPEN_ {}
 | CLOSE_ {ARDestroy dtwomass}
 ;

2massFrame : NEW_ {set _ new}
 | CURRENT_ {set _ current}
 ;

2massSurvey : 'j' {set _ $1}
 | 'h' {set _ $1}
 | 'k' {set _ $1}
 ;

3d : {Create3DFrame}
 | VIEW_ 3dView
 | VP_ 3dView
 | AZ_ numeric {global threed; set threed(az) $2; 3DViewPoint}
 | EL_ numeric {global threed; set threed(el) $2; 3DViewPoint}
 | SCALE_ numeric {global threed; set threed(scale) $2; 3DScale}
 | METHOD_ 3dMethod {global threed; set threed(method) $2; 3DRenderMethod}
 | BG_ 3dBackground {global threed; set threed(background) $2; 3DBackground}
 | BORDER_ 3dBorder
 | HIGHLITE_ 3dHighlite
 | COMPASS_ 3dCompass
 | OPEN_ {}
 | CLOSE_ {3DDestroyDialog}
 ;

3dView : numeric numeric {global threed; set threed(az) $1; set threed(el) $2; 3DViewPoint}
 ;

3dMethod : MIP_ {set _ mip}
 | AIP_ {set _ aip}
 ;

3dBackground : NONE_ {set _ none}
 | AZ_ {set _ azimuth}
 | EL_ {set _ elevation}
 ;

3dHighlite : yesno {global threed; set threed(highlite) $1; 3DHighlite}
 | COLOR_ STRING_ {global threed; set threed(highlite,color) $2; 3DHighliteColor}
 ;

3dBorder : yesno {global threed; set threed(border) $1; 3DBorder}
 | COLOR_ STRING_ {global threed; set threed(border,color) $2; 3DBorderColor}
 ;

3dCompass : yesno {global threed; set threed(compass) $1; 3DCompass}
 | COLOR_ STRING_ {global threed; set threed(compass,color) $2; 3DCompassColor}
 ;

align : {global current; set current(align) 1; AlignWCSFrame}
 | yesno {global current; set current(align) $1; AlignWCSFrame}
 ;

blink : {global current; set current(display) blink; DisplayMode}
 | yes {global current; set current(display) blink; DisplayMode}
 | no {global current; set current(display) single; DisplayMode}
 | INTERVAL_ numeric {global blink; set blink(interval) [expr int($2*1000)]; DisplayMode}
 ;

bin : CLOSE_ {BinDestroyDialog}
 | OPEN_ {BinDialog}
 | MATCH_ {MatchBinCurrent}
 | LOCK_ binLock
 | ABOUT_ binAbout
 | BUFFERSIZE_ int {global bin; set bin(buffersize) $2; ChangeBinBufferSize}
 | COLS_ STRING_ STRING_ {BinCols \"$2\" \"$3\" \"\"}
 | COLSZ_ STRING_ STRING_ STRING_ {BinCols \"$2\" \"$3\" \"$4\"}
 | FACTOR_ binFactor
 | DEPTH_ int {global bin; set bin(depth) $1; ChangeBinDepth}
 | FILTER_ STRING_ {BinFilter $2}
 | FUNCTION_ binFunction {global bin; set bin(function) $1; ChangeBinFunction}
 | IN_ {Bin .5 .5}
 | OUT_ {Bin 2 2}
 | TO_ binTo
 ;

binLock : {global bin; set bin(lock) 1; LockBinCurrent}
 | yesno {global bin; set bin(lock) $1; LockBinCurrent}
 ;

binAbout : numeric numeric {BinAbout $1 $2}
 | CENTER_ {BinAboutCenter}
 ;

binFactor : numeric {global bin; set bin(factor) " $1 $1 "; ChangeBinFactor}
 | numeric numeric {global bin; set bin(factor) " $1 $2 "; ChangeBinFactor}
 ;

binFunction: AVERAGE_ {set _ average}
 | SUM_ {set _ sum}
 ;

binTo: binFactor
 | FIT_ {BinToFit}
 ;

block : int {Block $1 $1}
 | int int {Block $1 $2}
 | OPEN_ {BlockDialog}
 | CLOSE_ {BlockDestroyDialog}
 | MATCH_ {MatchBlockCurrent}
 | LOCK_ blockLock
 | IN_ {Block .5 .5}
 | OUT_ {Block 2 2}
 | TO_ blockTo
 ;

blockLock : {global block; set block(lock) 1; LockBlockCurrent}
 | yesno {global block; set block(lock) $1; LockBlockCurrent}
 ;

blockTo : int {global block; set block(factor) " $1 $1 "; ChangeBlock}
 | int int {global block; set block(factor) " $1 $2 "; ChangeBlock}
 | FIT_ {BlockToFit}
 ; 

catalog : {CATTool}
 | LOAD_ catLoad
 | FILE_ catLoad
 | IMPORT_ catLoad
 | STRING_ {CatalogRefCmd $1} cat
 # backward compatibility
 | CDS_ STRING_ {CatalogRefCmd $2} cat
 | cat
 ;

catLoad: catLoadReader STRING_ {global icat; CATDialog cattool {} {} {} none; CATLoadFn [lindex $icat(cats) end] $2 $1; FileLast catfbox $2}
 | STRING_ {global icat; CATDialog cattool {} {} {} none; CATLoadFn [lindex $icat(cats) end] $1 VOTRead; FileLast catfbox $1}
 ;

catLoadReader : XML_ {set _ VOTRead}
 | VOT_ {set _ VOTRead}
 | SB_ {set _ starbase_read}
 | STARBASE_ {set _ starbase_read}
 | CSV_ {set _ TSVRead}
 | TSV_ {set _ TSVRead}
 ;

cat : ALLCOLS_ {global cvarname; global $cvarname; set ${cvarname}(allcols) 1}
 | ALLROWS_ {global cvarname; global $cvarname; set ${cvarname}(allrows) 1}
 | CANCEL_ {global cvarname; ARCancel $cvarname}
 | CLEAR_ {global cvarname; CATOff $cvarname}
 | CLOSE_ {global cvarname; CATDestroy $cvarname}
 | COORDINATE_ skycoord skyframe {global cvarname; global $cvarname; set ${cvarname}(x) $yy(x); set ${cvarname}(y) $yy(y); set ${cvarname}(sky) $yy(skyframe)}
 | CROSSHAIR_ {global cvarname; CATCrosshair $cvarname}
 | EDIT_ yesno {global cvarname; global $cvarname; set ${cvarname}(edit) $2; CATEdit $cvarname}
 | EXPORT_ catSave
 | FILTER_ catFilter
 | HEADER_ {global cvarname; CATHeader $cvarname}
 | HIDE_ {global cvarname; global $cvarname; set ${cvarname}(show) 0; CATGenerate $cvarname}
 | LOCATION_ int {global cvarname; global $cvarname; set ${cvarname}(loc) $2; CATGenerate $cvarname}
 | MATCH_ catMatch
 | MAXROWS_ int {global cvarname; global $cvarname; set ${cvarname}(max) $2}
 | NAME_ STRING_ {global cvarname; global $cvarname; set ${cvarname}(name) $2}
 | PANTO_ yesno {global cvarname; global $cvarname; set ${cvarname}(panto) $2}
 | PLOT_ STRING_ STRING_ STRING_ STRING_ {global cvarname; global $cvarname; set ${cvarname}(plot,x) $2; set ${cvarname}(plot,y) $3; set ${cvarname}(plot,xerr) $4; set ${cvarname}(plot,yerr) $5; CATPlotGenerate $cvarname}
 | PRINT_ {global cvarname; CATPrint $cvarname}
 | PSKY_ skyframe {global cvarname; global $cvarname; set ${cvarname}(psky) $2; CATGenerate $cvarname}
 | PSYSTEM_ wcssys {global cvarname; global $cvarname; set ${cvarname}(psystem) $2; CATGenerate $cvarname}
 | REGIONS_ {global cvarname; CATGenerateRegions $cvarname}
 | RETRIEVE_ {global cvarname; CATApply $cvarname 1}
 | SAMP_ catSAMP
 | SAVE_ catSave
 | SERVER_ STRING_ {global cvarname; global $cvarname; set ${cvarname}(server) $2}
 | SHOW_ {global cvarname; global $cvarname; set ${cvarname}(show) 1; CATGenerate $cvarname}
 | SIZE_ numeric numeric skydist {global cvarname; global $cvarname; set ${cvarname}(width) $1; set ${cvarname}(height) $2; set ${cvarname}(rformat) $3; set ${cvarname}(rformat,msg) $3}
 | SKY_ skyframe {global cvarname; global $cvarname; set ${cvarname}(sky) $1; CoordMenuButtonCmd $cvarname system sky [list CATWCSMenuUpdate $cvarname]}
 | SKYFORMAT_ skyformat {global cvarname; global $cvarname; set ${cvarname}(skyformat) $2}
 | SORT_ catSort
 | SYMBOL_ {global cvarname; global $cvarname; set ${cvarname}(row) 1} catSymbol
 | SYMBOL_ int {global cvarname; global $cvarname; set ${cvarname}(row) $2} catSymbol
 | SYSTEM_ wcssys {global cvarname; global $cvarname; set ${cvarname}(system) $1; CoordMenuButtonCmd $cvarname system sky [list CATWCSMenuUpdate $cvarname]}
 | UPDATE_ {global cvarname; CATUpdate $cvarname}
 | 'x' STRING_ {global cvarname; global $cvarname; set ${cvarname}(colx) $2; CATGenerate $cvarname}
 | RA_ STRING_ {global cvarname; global $cvarname; set ${cvarname}(colx) $2; CATGenerate $cvarname}
 | 'y' STRING_ {global cvarname; global $cvarname; set ${cvarname}(coly) $2; CATGenerate $cvarname}
 | DEC_ STRING_ {global cvarname; global $cvarname; set ${cvarname}(coly) $2; CATGenerate $cvarname}
 ;

catFilter : LOAD_ STRING_ {
  global cvarname
  global $cvarname
  if {[catch {open $2 r} fp]} {
    Error "[msgcat::mc {Unable to open file}] $2: $fp"
    yyerror
  }
  set flt [read -nonewline $fp]
  catch {regsub {\n} $flt " " $flt}
  set ${cvarname}(filter) [string trim $flt]
  catch {close $fp}
 }
 | STRING_ {global cvarname; global $cvarname; set ${cvarname}(filter) $1; CATable $cvarname}
 ;

catMatch : ERROR_ numeric skydist {global icat; set icat(error) $2; set icat(eformat) $3}
 | FUNCTION_ catMatchFunction {global icat;  set icat(function) $2}
 | UNIQUE_ yesno {global icat; set icat(unique) $2}
 | RETURN_ catMatchFunction {global icat;  set icat(return) $2}
 | STRING_ STRING_ {global current; global icat; set icat(match1) cat$1; set icat(match2) cat$2;CATMatch $current(frame) $icat(match1) $icat(match2)}
 ;

catMatchFunction : 1AND2_ {set _ 1and2}
 | 1NOT2_ {set _ 1not2}
 | 2NOT1_ {set _ 2not1}
 ;

catSAMP : {global cvarname; SAMPSendTableLoadVotable {} $cvarname}
 | BROADCAST_ {global cvarname; SAMPSendTableLoadVotable {} $cvarname}
 | SEND_ STRING_ {global cvarname; CatalogSAMPCmd $2}
 ;

catSave : catSaveWriter STRING_ {global cvarname; CATSaveFn $cvarname $2 $1; FileLast catfbox $2}
 | STRING_ {global cvarname; CATSaveFn $cvarname $1 VOTWrite; FileLast catfbox $1}
 ;

catSaveWriter : XML_ {set _ VOTWrite}
 | VOT_ {set _ VOTWrite}
 | SB_ {set _ starbase_write}
 | STARBASE_ {set _ starbase_write}
 | CSV_ {set _ TSVWrite}
 | TSV_ {set _ TSVWrite}
 ;

catSort : STRING_ {global cvarname; global $cvarname; set ${cvarname}(sort) $1; CATTable $cvarname}
 | STRING_ catSortDir {global cvarname; global $cvarname; set ${cvarname}(sort) $1; set ${cvarname}(sort,dir) $2; CATTable $cvarname}
 ;

catSortDir : INCR_ {set _ "-increasing"}
 | DECR_ {set _ "-decreasing"}
 ;

catSymbol : ADD_ {CatalogSymbolAddCmd}
 | ANGLE_ numeric {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) angle] $2; CATGenerate $cvarname}
 | COLOR_ STRING_ {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) color] $2; CATGenerate $cvarname}
 | CONDITION_ STRING_ {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) condition] $2; CATGenerate $cvarname}
 | FONT_ font {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) font] $2; CATGenerate $cvarname}
 | FONTSIZE_ int {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) fontsize] $2; CATGenerate $cvarname}
 | FONTWEIGHT_ fontweight {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) fontweight] $2; CATGenerate $cvarname}
 | FONTSLANT_ fontslant {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) fontslant] $2; CATGenerate $cvarname}
 | LOAD_ STRING_ {global cvarname; global $cvarname; CatalogSymbolLoadCmd $2}
 | REMOVE_ {global cvarname; global $cvarname; starbase_rowdel ${cvarname}(symdb) ${cvarname}(row); CATGenerate $cvarname}
 | SAVE_ STRING_ {global cvarname; global $cvarname; starbase_write ${cvarname}(symdb) $2}
 | SIZE_ numeric {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) size] $2; CATGenerate $cvarname}
 | SIZE2_ numeric {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) size2] $2; CATGenerate $cvarname}
 | SHAPE_ catSymbolShape {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) shape] $2; CATGenerate $cvarname}
 | TEXT_ STRING_ {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) text] $2; CATGenerate $cvarname}
 | UNITS_ STRING_ {global cvarname; global $cvarname; starbase_set ${cvarname}(symdb) ${cvarname}(row) [starbase_colnum ${cvarname}(symdb) units] $2; CATGenerate $cvarname}
 ;

catSymbolShape : POINT_ {set _ "circle point"}
 | CIRCLE_ POINT_ {set _ "circle point"}
 | BOX_ POINT_ {set _ "box point"}
 | DIAMOND_ POINT_ {set _ "diamond point"}
 | CROSS_ POINT_ {set _ "cross point"}
 | 'x' POINT_ {set _ "x point"}
 | ARROW_ POINT_ {set _ "arrow point"}
 | BOXCIRCLE_ POINT_ {set _ "boxcircle point"}
 | CIRCLE_ {set _ circle}
 | ELLIPSE_ {set _ ellipse}
 | BOX_ {set _ box}
 | TEXT_ {set _ text}
 ;

cd : STRING_ {cd $2}
 | '.' {cd .}
 | '/' {cd /}
 ;

cmap : STRING_ {CmapCmd $1}
 | OPEN_ {ColormapDialog}
 | CLOSE_ {ColormapDestroyDialog}
# backward compatibility
 | MATCH_ {MatchColorCurrent}
# backward compatibility
 | LOCK_ cmapLock
 | LOAD_ cmapLoad
 | FILE_ cmapLoad
 | SAVE_ STRING_ {SaveColormapFile $1; FileLast colormapfbox $1}
 | INVERT_ yesno {global colorbar; set colorbar(invert) $2; InvertColorbar}
 | TAG_ cmapTag
 | VALUE_ numeric numeric {CmapValueCmd $2 $3}
 ;

cmapLock : {global colorbar; set colorbar(lock) 1; LockColorCurrent}
 | yesno {global colorbar; set colorbar(lock) $1; LockColorCurrent}
 ;

cmapLoad : STRING_ {LoadColormapFile $1; FileLast colormapfbox $1}
 ;

cmapTag : LOAD_ STRING_ {LoadColorTag $2}
 | SAVE_ STRING_ {global current; $current(colorbar) tag save $2}
 | DELETE_ {DeleteColorTag}
 ;

crop : skycoord numeric numeric {global yy; global current; $current(frame) crop center $yy(x) $yy(y) image fk5 $2 $3 image degrees}
 | skycoord numeric numeric coordsys {global yy; global current; $current(frame) crop center $yy(x) $yy(y) $4 fk5 $2 $3 $4 degrees}
 | skycoord numeric numeric coordsys skyframe {global yy; global current; $current(frame) crop center $yy(x) $yy(y) $4 $5 $2 $3 $4 degrees}
 | skycoord numeric numeric coordsys skyframe skydist {global yy; global current; $current(frame) crop center $yy(x) $yy(y) $4 $5 $2 $3 $4 $6}
 | skycoord numeric numeric skyframe {global yy; global current; $current(frame) crop center $yy(x) $yy(y) wcs $4 $2 $3 wcs degrees}
 | skycoord numeric numeric skyframe skydist {global yy; global current; $current(frame) crop center $yy(x) $yy(y) wcs $4 $2 $3 wcs $5}

 | OPEN_ {CropDialog}
 | CLOSE_ {CropDestroyDialog}
 | MATCH_ coordsys {MatchCropCurrent $2}
 | LOCK_ coordsys {global crop; set crop(lock) $2; LockCropCurrent}
 | LOCK_ NONE_ {global crop; set crop(lock) none; LockCropCurrent}
 | RESET_ {CropReset}
 | 3D_ numeric numeric {global current; $current(frame) crop 3d $2 $3 image}
 | 3D_ numeric numeric coordsys {global current; $current(frame) crop 3d $2 $3 $4}
 ;

crosshair : skycoord {global yy; CrosshairTo $yy(x) $yy(y) image fk5}
 | skycoord coordsys {global yy; CrosshairTo $yy(x) $yy(y) $2 fk5}
 | skycoord coordsys skyframe {global yy; CrosshairTo $yy(x) $yy(y) $2 $3}
 | skycoord skyframe {global yy; CrosshairTo $yy(x) $yy(y) wcs $2}
 | MATCH_ coordsys {global crosshair; MatchCrosshairCurrent $2}
 | LOCK_ coordsys {global crosshair; set crosshair(lock) $2; LockCrosshairCurrent}
 | LOCK_ NONE_ {global crosshair; set crosshair(lock) none; LockCrosshairCurrent}
 ;

cube : cubeSlice
 | OPEN_ {}
 | CLOSE_ {CubeDestroyDialog}
 | MATCH_ cubeMatch
 | LOCK_ cubeLock
 | PLAY_ {CubePlay}
 | STOP_ {CubeStop}
 | NEXT_ {CubeNext}
 | PREV_ {CubePrev}
 | FIRST_ {CubeFirst}
 | LAST_ {CubeLast}
 | INTERVAL_ numeric {global blink; set blink(interval) [expr int($2*1000)]}
 | AXIS_ int {global cube; set cube(axis) [expr $2-1]}
 | AXES_ cubeAxes
 | ORDER_ cubeAxes
 ;

cubeSlice : int {global dcube; global cube; set dcube(wcs,2) $1; set cube(system) image; set cube(axis) 2; CubeApply 2}
 | numeric coordsys {global dcube; global cube; set dcube(wcs,2) $1; set cube(system) $2; set cube(axis) 2; CubeApply 2}
 | numeric coordsys int {global dcube; global cube; set aa [expr $3-1]; set dcube(wcs,$aa) $1; set cube(system) $2; set cube(axis) $aa; CubeApply $aa}
 ;

cubeMatch : {MatchCubeCurrent image}
 | coordsys {MatchCubeCurrent $1}
 ;

cubeLock : {global cube; set cube(lock) image; LockCubeCurrent}
 | yes {global cube; set cube(lock) image; LockCubeCurrent}
 | no {global cube; set cube(lock) none; LockCubeCurrent}
 | coordsys {global cube; set cube(lock) $1; LockCubeCurrent}
 | NONE_ {global cube; set cube(lock) none; LockCubeCurrent}
 ;

cubeAxes : cubeAxesOrder {global cube; set cube(axes) $1; CubeAxes}
 | LOCK_ cubeAxesLock
 ;

cubeAxesOrder : 123_ {set _ 123}
 | 132_ {set _ 132}
 | 213_ {set _ 213}
 | 231_ {set _ 231}
 | 312_ {set _ 312}
 | 321_ {set _ 321}
 ;

cubeAxesLock : {global cube; set cube(lock,axes) 1; LockAxesCurrent}
 | yesno {global cube; set cube(lock,axes) $1; LockAxesCurrent}
 ;

fits : {global file; set file(type) fits}
 | MOSAIC_ mosaicType {global file; set file(type) mosaic; set file(mosaic) $2}
 | MOSAICIMAGE_ mosaicImageType {global file; set file(type) mosaicimage; set file(mosaic) $2}
 | MECUBE_ {global file; set file(type) mecube}
 | MULTIFRAME_ {global file; set file(type) multiframe}
 | RGBCUBE_ {global file; set file(type) rgbcube}
 | RGBIMAGE_ {global file; set file(type) rgbimage}
 ;

frame : int {CreateGotoFrame $1 base}
 | MATCH_ coordsys {MatchFrameCurrent $2}
 | LOCK_ frameLock
 | CENTER_ frameCenter
 | CLEAR_ frameClear
 | DELETE_ frameDelete
 | NEW_ frameNew
 | RESET_ frameReset
 | REFRESH_ frameRefresh
 | HIDE_ frameHide
 | SHOW_ frameShow
 | MOVE_ frameMove
 | FIRST_ {FirstFrame}
 | PREV_ {PrevFrame}
 | NEXT_ {NextFrame}
 | LAST_ {LastFrame}
 | FRAMENO_ int {CreateGotoFrame $2 base}
 ;

frameLock : coordsys {global panzoom; set panzoom(lock) $1; LockFrameCurrent}
 | NONE_ {global panzoom; set panzoom(lock) none; LockFrameCurrent}
 ;

frameCenter: {CenterCurrentFrame}
 | ALL_ {CenterAllFrame}
 | int {CenterFrame Frame$1}
 ;

frameClear: {ClearCurrentFrame}
 | ALL_ {ClearAllFrame}
 | int {ClearFrame Frame$1}
 ;

frameDelete: {DeleteCurrentFrame}
 | ALL_ {DeleteAllFrames}
 | int {DeleteSingleFrame Frame$1}
 ;

frameNew: {CreateFrame}
 | RGB_ {CreateRGBFrame}
 | 3D_ {Create3DFrame}
 ;

frameReset: {ResetCurrentFrame}
 | ALL_ {ResetAllFrame}
 | int {ResetFrame Frame$1}
 ;

frameRefresh: {UpdateCurrentFrame}
 | ALL_ {UpdateAllFrame}
 | int {UpdateFrame Frame$1}
 ;

frameHide: {global active; global current; set active($current(frame)) 0; UpdateActiveFrames}
 | ALL_ {ActiveFrameNone}
 | int {global active; set active(Frame$1) 0; UpdateActiveFrames}
 ;

frameShow: {}
 | ALL_ {ActiveFrameAll}
 | int {global active; set active(Frame$1) 1; UpdateActiveFrames}
 ;

frameMove : FIRST_ {MoveFirstFrame}
 | BACK_ {MovePrevFrame}
 | FORWARD_ {MoveNextFrame}
 | LAST_ {MoveLastFrame}
 ;

iconify : {global ds9; wm iconify $ds9(top)}
 | yes {global ds9; wm iconify $ds9(top)}
 | no {global ds9; wm deiconify $ds9(top)}
 ;

minmax : {global scale; set scale(mode) minmax; ChangeScaleMode}
 # backward compatibility
 | AUTO_ {global minmax; set minmax(mode) scan; ChangeMinMax}
 | SCAN_ {global minmax; set minmax(mode) scan; ChangeMinMax}
 | SAMPLE_ {global minmax; set minmax(mode) sample; ChangeMinMax}
 | DATAMIN_ {global minmax; set minmax(mode) datamin; ChangeMinMax}
 | IRAFMIN_ {global minmax; set minmax(mode) irafmin; ChangeMinMax}
 | MODE_ minmaxMode {global minmax; set minmax(mode) $2; ChangeMinMax}
 | INTERVAL_ int {global minmax; set minmax(sample) $2; ChangeMinMax}
 ;

minmaxMode : SCAN_ {set _ scan}
 | SAMPLE_ {set _ sample}
 | DATAMIN_ {set _ datamin}
 | IRAFMIN_ {set _ irafmin}
 ;

mode : NONE_ {global current; set current(mode) none; ChangeMode}
 # backward compatibility
 | POINTER_ {global current; set current(mode) none; ChangeMode}
 | REGION_ {global current; set current(mode) region; ChangeMode}
 | CROSSHAIR_ {global current; set current(mode) crosshair; ChangeMode}
 | COLORBAR_ {global current; set current(mode) colorbar; ChangeMode}
 | PAN_ {global current; set current(mode) pan; ChangeMode}
 | ZOOM_ {global current; set current(mode) zoom; ChangeMode}
 | ROTATE_ {global current; set current(mode) rotate; ChangeMode}
 | CROP_ {global current; set current(mode) rotate; ChangeMode}
 | CATALOG_ {global current; set current(mode) catalog; ChangeMode}
 | EXAMINE_ {global current; set current(mode) examine; ChangeMode}
 ;

orient : orientation {global current; set current(orient) $1; ChangeOrient}
 | OPEN_ {PanZoomDialog}
 | CLOSE_ {PanZoomDestroyDialog}
 ;

orientation : NONE_ {set _ none}
 | 'x' {set _ x}
 | 'y' {set _ y}
 | XY_ {set _ xy}
 ;

pan : {}
 | OPEN_ {PanZoomDialog}
 | CLOSE_ {PanZoomDestroyDialog}
 | TO_ panTo
 ;

panTo : {}
 ;

pixelTable : {PixelTableDialog}
 | yes {PixelTableDialog}
 | OPEN_ {PixelTableDialog}
 | no {PixelTableDestroyDialog}
 | CLOSE_ {PixelTableDestroyDialog}
 ;

prefs : CLEAR_ {ClearPrefs}
 # backward compatibility
 | BGCOLOR_ STRING_ {global pds9; set pds9(bg) $2; PrefsBgColor}
 # backward compatibility
 | NANCOLOR_ STRING_ {global pds9; set pds9(nan) $2; PrefsNanColor}
 # backward compatibility
 | THREADS_ int {global pds9; set ds9(threads) $2; ChangeThreads}
 | IRAFALIGN_ yesno {global pds9; set pds9(iraf) $2; PrefsIRAFAlign}
 ;

rgb : {CreateRGBFrame}
 | OPEN_ {}
 | CLOSE_ {RGBDestroyDialog}
 | RED_ {global current; set current(rgb) red; RGBChannel}
 | GREEN_ {global current; set current(rgb) green; RGBChannel}
 | BLUE_ {global current; set current(rgb) blue; RGBChannel}
 | CHANNEL_ rgbChannel {global current; set current(rgb) $2; RGBChannel}
 | LOCK_ rgbLock
 | SYSTEM_ coordsys {global rgb; set rgb(system) $2; RGBSystem}
 | VIEW_ rgbView
 ;

rgbChannel : RED_ {set _ red}
 | GREEN_ {set _ green}
 | BLUE_ {set _ blue}
 ;

rgbLock : WCS_ rgbLockWCS
 | CROP_ rgbLockCrop
 | SLICE_ rgbLockSlice
 | BIN_ rgbLockBin
 | AXES_ rgbLockAxes
 | ORDER_ rgbLockAxes
 | SCALE_ rgbLockScale
 | LIMITS_ rgbLockScalelimits
 | SCALELIMITS_ rgbLockScalelimits
 | COLOR_ rgbLockColorbar
 | COLORMAP_ rgbLockColorbar
 | COLORBAR_ rgbLockColorbar
 | BLOCK_ rgbLockBlock
 | SMOOTH_ rgbLockSmooth
 ;

rgbLockWCS: {global rgb; set rgb(lock,wcs) 1;}
 | yesno {global rgb; set rgb(lock,wcs) $1;}
 ;

rgbLockCrop: {global rgb; set rgb(lock,crop) 1;}
 | yesno {global rgb; set rgb(lock,crop) $1;}
 ;

rgbLockSlice: {global rgb; set rgb(lock,slice) 1;}
 | yesno {global rgb; set rgb(lock,slice) $1;}
 ;

rgbLockBin: {global rgb; set rgb(lock,bin) 1;}
 | yesno {global rgb; set rgb(lock,bin) $1;}
 ;

rgbLockAxes: {global rgb; set rgb(lock,axes) 1;}
 | yesno {global rgb; set rgb(lock,axes) $1;}
 ;

rgbLockScale: {global rgb; set rgb(lock,scale) 1;}
 | yesno {global rgb; set rgb(lock,scale) $1;}
 ;

rgbLockScalelimits: {global rgb; set rgb(lock,scalelimits) 1;}
 | yesno {global rgb; set rgb(lock,scalelimits) $1;}
 ;

rgbLockColorbar: {global rgb; set rgb(lock,colorbar) 1;}
 | yesno {global rgb; set rgb(lock,colorbar) $1;}
 ;

rgbLockBlock: {global rgb; set rgb(lock,block) 1;}
 | yesno {global rgb; set rgb(lock,block) $1;}
 ;

rgbLockSmooth: {global rgb; set rgb(lock,smooth) 1;}
 | yesno {global rgb; set rgb(lock,smooth) $1;}
 ;

rgbView : RED_ yesno {global rgb; set rgb(red) $2; RGBView}
 | GREEN_ yesno {global rgb; set rgb(green) $2; RGBView}
 | BLUE_ yesno {global rgb; set rgb(blue) $2; RGBView}
 ;

rotate : numeric {Rotate $1}
 | OPEN_ {PanZoomDialog}
 | CLOSE_ {PanZoomDestroyDialog}
 | TO_ numeric {global current; set current(rotate) $2; ChangeRotate}
 ;

scale : scaleScales {global scale; set scale(type) $1; ChangeScale}
 | LOG_ scaleLog
 | DATASEC_ yesno
 | LIMITS_ scaleLimits
 | SCALELIMITS_ scaleLimits
 | MINMAX_ {global scale; set scale(mode) minmax; ChangeScaleMode}
 | ZSCALE_ {global scale; set scale(mode) zscale; ChangeScaleMode}
 | ZMAX_ {global scale; set scale(mode) zmax; ChangeScaleMode}
 | USER_ {global scale; set scale(mode) user; ChangeScaleMode}
 | MODE_ scaleMode {global scale; set scale(mode) $2; ChangeScaleMode}
 | MODE_ numeric {global scale; set scale(mode) $2; ChangeScaleMode}
 | LOCAL_ {global scale; set scale(scope) local; ChangeScaleScope}
 | GLOBAL_ {global scale; set scale(scope) global; ChangeScaleScope}
 | SCOPE_ scaleScope {global scale; set scale(scope) $2; ChangeScaleScope}
 | MATCH_ {MatchScaleCurrent} 
 | MATCH_ LIMITS_ {MatchScaleLimitsCurrent}
 | MATCH_ SCALELIMITS_ {MatchScaleLimitsCurrent}
 | LOCK_ {global scale; set scale(lock) 1; LockScaleCurrent} 
 | LOCK_ yesno {global scale; set scale(lock) $2; LockScaleCurrent}
 | LOCK_ LIMITS_ {global scale; set scale(lock,limits) 1; LockScaleLimitsCurrent} 
 | LOCK_ LIMITS_ scaleLockLimits
 | LOCK_ SCALELIMITS_ {global scale; set scale(lock,limits) 1; LockScaleLimitsCurrent} 
 | LOCK_ SCALELIMITS_ scaleLockLimits
 | OPEN_ {ScaleDialog}
 | CLOSE_ {ScaleDestroyDialog}
 ;

scaleScales : LINEAR_ {set _ linear}
 | POW_ {set _ pow}
 | SQRT_ {set _ sqrt}
 | SQUARED_ {set _ squared}
 | ASINH_ {set _ asinh}
 | SINH_ {set _ sinh}
 | HISTEQU_ {set _ histequ}
 ;

scaleLog : {global scale; set scale(type) log; ChangeScale}
 | EXP_ numeric {global scale; set scale(log) $2; ChangeScale}
 ;

scaleLimits: numeric numeric {global scale; set scale(min) $1; set scale(max) $2; ChangeScaleLimit}
 ;
	     
scaleLockLimits : yesno {global scale; set scale(lock,limits) $1; LockScaleLimitsCurrent}
 ;

scaleMode : MINMAX_ {set _ minmax}
 | ZSCALE_ {set _ zscale}
 | ZMAX_ {set _ zmax}
 ;

scaleScope : LOCAL_ {set _ local}
 | GLOBAL_ {set _ global}
 ;

sleep : {after 1000}
 | numeric {after [expr int($1*1000)]}
 ;

tile: {global current; set current(display) tile; DisplayMode}
 | yes {global current; set current(display) tile; DisplayMode}
 | no {global current; set current(display) single; DisplayMode}
 | MODE_ tileMode {global tile; set tile(mode) $2; DisplayMode}
 | GRID_ tileGrid
 | COLUMN_ {global tile; set tile(mode) column; DisplayMode}
 | ROW_ {global tile; set tile(mode) row; DisplayMode}
 ;

tileMode : GRID_ {set _ grid}
 | COLUMN_ {set _ column}
 | ROW_ {set _ row}
 ;

tileGrid : {global tile; set tile(mode) grid; DisplayMode}
 | MODE_ tileGridMode {global tile; set tile(grid,mode) $2; DisplayMode}
 | DIRECTION_ tileGridDir {global tile; set tile(grid,dir) $2; DisplayMode}
 | LAYOUT_ int int {global tile; set tile(grid,col) $2; set tile(grid,row) $3; set tile(grid,mode) manual; DisplayMode}
 | GAP_ int {global tile; set tile(grid,gap) $2; DisplayMode}
 ;

tileGridMode : AUTOMATIC_ {set _ automatic}
 | MANUAL_ {set _ manual}
 ;

tileGridDir : 'x' {set _ x}
 | 'y' {set _ y}
 ;

wcs : OPEN_ {WCSDialog}
 | CLOSE_ {WCSDestroyDialog}
 | SYSTEM_ wcssys {global wcs; set wcs(system) $2; UpdateWCS}
 | SKY_ skyframe {global wcs; set wcs(sky) $2; UpdateWCS}
 | FORMAT_ skyformat {global wcs; set wcs(skyformat) $2; UpdateWCS}
 | SKYFORMAT_ skyformat {global wcs; set wcs(skyformat) $2; UpdateWCS}
 | ALIGN_ yesno {global current; set current(align) $2; AlignWCSFrame}
 | RESET_ {WCSResetCmd 1}
 | RESET_ int {WCSResetCmd $2} 
 | REPLACE_ STRING_
 | REPLACE_ int STRING_
 | APPEND_ STRING_
 | APPEND_ int STRING_
 | wcssys {global wcs; set wcs(system) $1; UpdateWCS}
 | skyframe {global wcs; set wcs(sky) $1; UpdateWCS}
 | skyformat {global wcs; set wcs(skyformat) $1; UpdateWCS}
 ;

zoom : numeric {Zoom $1 $1}
 | numeric numeric {Zoom $1 $2}
 | OPEN_ {PanZoomDialog}
 | CLOSE_ {PanZoomDestroyDialog}
 | IN_ {Zoom 2 2}
 | OUT_ {Zoom .5 .5}
 | TO_ zoomTo
 ;

zoomTo: FIT_ {ZoomToFit}
 | numeric {global zoom; set current(zoom) " $1 $1 "; ChangeZoom}
 | numeric numeric {global zoom; set current(zoom) " $1 $2 "; ChangeZoom}
 ;

zscale : {global scale; set scale(mode) zscale; ChangeScaleMode}
 | CONTRAST_ numeric {global zscale; set zscale(contrast) $2; ChangeZScale}
 | SAMPLE_ int {global zscale; set zscale(sample) $2; ChangeZScale}
 | LINE_ int {global zscale; set zscale(line) $2; ChangeZScale}
 ;

%%

proc yyerror {s} {
     puts stderr "parse error:"
     puts stderr "$::yy_buffer"
     puts stderr [format "%*s" $::yy_index ^]
}
