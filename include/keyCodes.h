/*
 * Part of the PX-Engine project - https://github.com/angelotadres/px-engine
 *
 * Copyright 2025 Angelo Tadres
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

namespace pxe {
	/**
	 * @brief Enum representing key codes in the engine.
	 *
	 * These values map directly to GLFW key codes.
	 */
	enum class KeyCode : int {
		Unknown = -1,

		// Numbers
		Num0 = 48,
		Num1 = 49,
		Num2 = 50,
		Num3 = 51,
		Num4 = 52,
		Num5 = 53,
		Num6 = 54,
		Num7 = 55,
		Num8 = 56,
		Num9 = 57,

		// Letters (A-Z)
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		// World keys (for international keyboards)
		World1 = 161,
		World2 = 162,

		// Lock and Special System Keys
		CapsLock     = 280,
		ScrollLock   = 281,
		NumLock      = 282,
		PrintScreen  = 283,
		Pause        = 284,

		// Function Keys (F1-F25)
		F1  = 290,
		F2  = 291,
		F3  = 292,
		F4  = 293,
		F5  = 294,
		F6  = 295,
		F7  = 296,
		F8  = 297,
		F9  = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		// Special Keys
		Space      = 32,
		Escape     = 256,
		Enter      = 257,
		Tab        = 258,
		Backspace  = 259,
		Insert     = 260,
		Delete     = 261,
		RightArrow = 262,
		LeftArrow  = 263,
		DownArrow  = 264,
		UpArrow    = 265,
		PageUp     = 266,
		PageDown   = 267,
		Home       = 268,
		End        = 269,

		// Modifiers and Meta Keys
		LeftShift  = 340,
		RightShift = 344,
		LeftCtrl   = 341,
		RightCtrl  = 345,
		LeftAlt    = 342,
		RightAlt   = 346,
		LeftSuper  = 343,
		RightSuper = 347,
		Menu       = 348,

		// Punctuation & Special Characters
		Apostrophe   = 39,  // '
		Comma        = 44,  // ,
		Minus        = 45,  // -
		Period       = 46,  // .
		Slash        = 47,  // /
		Semicolon    = 59,  // ;
		Equal        = 61,  // =
		LeftBracket  = 91,  // [
		Backslash    = 92,  // \
		RightBracket = 93,  // ]
		GraveAccent  = 96,  // `

		// Numpad Keys
		KP0       = 320,
		KP1       = 321,
		KP2       = 322,
		KP3       = 323,
		KP4       = 324,
		KP5       = 325,
		KP6       = 326,
		KP7       = 327,
		KP8       = 328,
		KP9       = 329,
		KPDecimal = 330,
		KPDivide  = 331,
		KPMultiply= 332,
		KPSubtract= 333,
		KPAdd     = 334,
		KPEnter   = 335,
		KPEqual   = 336,
	};

	/**
	 * @brief Enum representing mouse buttons.
	 *
	 * These values map directly to GLFW mouse button codes.
	 */
	enum class MouseButton : int { Left = 0, Right = 1, Middle = 2 };
} // namespace pxe
