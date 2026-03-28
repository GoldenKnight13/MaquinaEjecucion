#pragma once

//Codigos de 
enum StatusCode : int{

	//Termino
	ENDED = 0,

	//Errores
	LECTURE_ERROR = 1,
	PROGRAM_SIZE_LIMIT_ERROR = 2,
	SYNTAX_ERROR = 3,
	REGISTER_INDEX_ERROR = 4,
	MEMORY_OVERFLOW_ERROR = 5,
	ARITH_ERROR = 6,
	INPUT_ERROR = 7,
	MEMORY_ACCESS_ERROR = 8,

	//Codigos internos
	CONTINUE = 100,

};