token_to_string_tbl = {
	128: "tEOF",
	129: "tINTEGER",
	130: "tFLOAT",
	131: "tSTRING",
	132: "tIDENTIFIER",
	133: "tBREAK",
	134: "tCONTINUE",
	135: "tDELETE",
	136: "tELSE",
	137: "tFOR",
	138: "tFUNCTION",
	139: "tIF",
	140: "tIN",
	141: "tNEW",
	142: "tRETURN",
	143: "tTHIS",
	144: "tTYPEOF",
	145: "tVAR",
	146: "tVOID",
	147: "tWHILE",
	148: "tWITH",
	149: "tCASE",
	150: "tCATCH",
	151: "tCLASS",
	152: "tCONST",
	153: "tDEBUGGER",
	154: "tDEFAULT",
	155: "tDO",
	156: "tENUM",
	157: "tEXPORT",
	158: "tEXTENDS",
	159: "tFINALLY",
	160: "tIMPORT",
	161: "tSUPER",
	162: "tSWITCH",
	163: "tTHROW",
	164: "tTRY",
	165: "tNULL",
	166: "tTRUE",
	167: "tFALSE",
	168: "tEQUAL",
	169: "tNEQUAL",
	170: "tLE",
	171: "tGE",
	172: "tAND",
	173: "tOR",
	174: "tPLUSPLUS",
	175: "tMINUSMINUS",
	176: "tMULA",
	177: "tDIVA",
	178: "tMODA",
	179: "tADDA",
	180: "tSUBA",
	181: "tANDA",
	182: "tXORA",
	183: "tORA",
	184: "tLSIA",
	185: "tLSHIFT",
	186: "tRSHIFT",
	187: "tRRSHIFT",
	188: "tRSIA",
	189: "tRRSA",
	190: "tSEQUAL",
	191: "tSNEQUAL"
};
function token_to_string(token) {
	var str = token_to_string_tbl[token];
	return (str == undefined) ? String.fromCharCode(token) : str;
}
