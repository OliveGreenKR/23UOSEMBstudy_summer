#include "pch.h"
#include "Vec.h"


/*
template함수를 헤더에 넣는 이유.

컴파일러가 해당 cpp파일로 object를 만들어도 따로 타입을 명시하지 않으면

특정 타입에 대한 함수를 찾을 수 없기 때문.

따라서 템플릿 함수는 header안에 정의해야 한다.

*/