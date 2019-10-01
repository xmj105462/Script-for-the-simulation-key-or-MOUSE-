#pragma once
#ifndef MAN_H
#define MAN_H
typedef struct Position Pos;
typedef struct DateLink DLhead;
typedef DateLink* DateLink_ptr;
typedef struct LinkStack LS;
constexpr auto MAP_X = 6;
constexpr auto MAP_Y = 6;
	void initPosition(DLhead& head, LS& ls);
	void move(LS& ls, DLhead& head);
	bool judge(LS& ls, DLhead& head);
	void initFrame();


#endif // !MAN_H
