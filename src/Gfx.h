/*
 *  Copyright (C) 2010 Florent Bedoiseau (buzz.computer@free.fr)
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __GFX_H__
#define __GFX_H__

//#ifdef __cplusplus
//extern "C" {
//#endif

#include <SDL.h>  

#ifdef GIF_SUPPORT
#include "gif_lib.h"
#endif

#include "Platform.h"

# ifdef PSP
#define GFX_SCREEN_W 480
#define GFX_SCREEN_H 272
# else
#define GFX_SCREEN_W 256
#define GFX_SCREEN_H 192
# endif

#define GFX_CHAR_W (GFX_SCREEN_W / FONT_WIDTH)
#define GFX_CHAR_H (GFX_SCREEN_H / FONT_WIDTH)

#define GFX_SCREEN_SIZE (GFX_SCREEN_H * GFX_SCREEN_W)
//#define GFX_SCREEN_DEPTH 8
#define GFX_SCREEN_DEPTH 16 
//#define GFX_SCREEN_DEPTH 24 

#define FONT_WIDTH 8
#define FONT_HEIGHT 8

// Keys
#define GFX_KEY_NONE   SDLK_UNKNOWN
#define GFX_KEY_DOWN   SDLK_DOWN
#define GFX_KEY_UP     SDLK_UP
#define GFX_KEY_LEFT   SDLK_LEFT 
#define GFX_KEY_RIGHT  SDLK_RIGHT 
#define GFX_KEY_ESC    SDLK_ESCAPE
#define GFX_KEY_ENTER  SDLK_RETURN
#define GFX_KEY_QUIT   SDLK_WORLD_18
#define GFX_KEY_SPACE  SDLK_SPACE
#define GFX_KEY_TAB    SDLK_TAB
#define GFX_KEY_RCTRL  SDLK_RCTRL
#define GFX_KEY_LCTRL  SDLK_LCTRL
#define GFX_KEY_LALT   SDLK_LALT
#define GFX_KEY_RALT   SDLK_RALT
#define GFX_KEY_RSHIFT SDLK_RSHIFT
#define GFX_KEY_LSHIFT SDLK_LSHIFT
#define GFX_KEY_BACKSPACE SDLK_BACKSPACE
#define GFX_KEY_F1     SDLK_F1





#define GFX_KEY_PRESSED  SDL_KEYDOWN
#define GFX_KEY_RELEASED SDL_KEYDOWNUP

typedef SDL_Surface gfxbitmap;

typedef enum {
  Iso8859_01 = 0,
  Iso8859_02,
  Iso8859_03,
  Iso8859_04,
  Iso8859_05,
  Iso8859_06,
  Iso8859_07,
  Iso8859_08,
  Iso8859_09,
  Iso8859_10
} FontClass;

// Graphical routines
void GfxInit ();
bool GfxInitWH (UInt16 w, UInt16 h);
void GfxQuit ();
void GfxUpdate ( ); // Simu only
UInt16 GfxGetScreenW();
UInt16 GfxGetScreenH();

void putpixel(gfxbitmap *surface, UInt16 x, UInt16 y, UInt32 pixel);
UInt32 getpixel(gfxbitmap *surface, UInt16 x, UInt16 y);

// Keys and Mouse
void GfxGetMouseXY (UInt16 *x, UInt16 *y);
UInt8 GfxGetMouseButton ();
UInt8 GfxKeyTouched ();
void GfxWaitTouched ();
UInt16 GfxKeyPressed ();
bool isGfxKeyPressed (UInt16 keycode);

gfxbitmap *GfxCreateBitmap (UInt16 w, UInt16 h);
gfxbitmap *GfxCreateBitmapFromPixmap (UInt16 w, UInt16 h, unsigned char *pixmap);
gfxbitmap *GfxCreateBitmapFromGif (const char *giffile);
void GfxDeleteBitmap (gfxbitmap *bitmap);

// Screen only
void GfxLocate (UInt16 l, UInt16 c);
void GfxChar (UInt8 ch, UInt8 fgColor, UInt32 bgColor);
void GfxString (const char *str, UInt32 fgColor, UInt32 bgColor);

// Screen and/or bitmap
void GfxClear (gfxbitmap *bitmap, UInt32 color);
UInt32 GfxColor (UInt8 r, UInt8 v, UInt8 b);
void GfxSelectFont (FontClass fnt);

void GfxStringWidth (const char *str, UInt16 &w, UInt16 &h);
UInt16 GfxStringH (const char *str);
UInt16 GfxStringW (const char *str);

void GfxStringXY(gfxbitmap *bitmap, const char *str, UInt16 x, UInt16 y, UInt32 fgColor, UInt32 bgColor);
void GfxCharXY (gfxbitmap *bitmap, UInt8 ch, UInt16 x, UInt16 y, UInt32 fgColor, UInt32 bgColor);
void GfxPixel (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt32 color);
UInt32 GfxColorPixel (gfxbitmap *bitmap, UInt16 x, UInt16 y);
void GfxLine (gfxbitmap *bitmap, UInt16 x1, UInt16 y1, UInt16 x2, UInt16 y2, UInt32 color);
void GfxDrawPixmap (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt16 w, UInt16 h, unsigned char *pixmap);
void GfxRectangle (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt16 w, UInt16 h, UInt32 color);
void GfxFillRectangle (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt16 w, UInt16 h, UInt32 color);
void GfxCircle (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt16 radius, UInt32 color);

void GfxBlit (gfxbitmap *src_bitmap, gfxbitmap *dst_bitmap, UInt16 x_src, UInt16 y_src, UInt16 x_dst, UInt16 y_dst , UInt16 width, UInt16 height);
void GfxSetNoClip (gfxbitmap *bitmap);
void GfxSetClip (gfxbitmap *bitmap, UInt16 x, UInt16 y, UInt16 witdh, UInt16 height);
void GfxGetClip (gfxbitmap *bitmap, UInt16 &x, UInt16 &y, UInt16 &w, UInt16 &h); 

void GfxWaitForVBL();

//#ifdef __cplusplus
//}
//#endif
#endif
