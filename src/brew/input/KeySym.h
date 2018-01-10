/**
 *
 *  |_  _ _
 *  |_)| (/_VV
 *
 *  Copyright 2015-2018 [insert fancy company name here]
 *
 *  Created on: May 30, 2016
 *
 */

#ifndef BREW_KEYSYM_H
#define BREW_KEYSYM_H

#include <ostream>

namespace brew {

/**
 * Symbols for western keyboard layouts.
 */
enum class KeySym
{
    Back,
	Delete,
	Down,
	End,
	Equals,
	Escape,
	Grave,
	Home,
	LeftControl,
	Left,
	LeftMenu,
	LeftShift,
	Minus,
	PageDown,
	PageUp,
	RightControl,
	Return,
	RightMenu,
	Right,
	RightShift,
	Space,
	SysReq,
	Tab,
	Up,
    Num0,Num1,Num2,Num3,Num4,Num5,Num6,Num7,Num8,Num9,
	Digit0, Digit1, Digit2, Digit3, Digit4, Digit5, Digit6, Digit7, Digit8, Digit9,
	A,B,C,D,E,F,G,H,I,J,K,L,M,N,O,P,Q,R,S,T,U,V,W,X,Y,Z,
	a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z,
    F1,F2,F3,F4,F5,F6,F9,F10,F11,F12,
	Undefined
};

/**
 * Prints the given key symbol to the output stream.
 * @param stream The output stream.
 * @param keySym The key symbol.
 * @return The output stream for chaining.
 */
std::ostream& operator << (std::ostream& stream, const KeySym& keySym);

} /* namespace brew */

#endif /* BREW_KEYSYM_H */
