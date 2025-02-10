#include "error.h"
#include "indulc.h"

#include <string.h>
static char**	alloc_arr(char* str1, char* str2)// tmp
{
	size_t	len = 1 + (str2 != NULL);
	char**	arr = malloc((len + 1) * sizeof(char *));
	arr[len] = NULL;
	arr[0] = strdup(str1);
	if (str2 != NULL)
		arr[1] = strdup(str2);
	return (arr);
}

static bool	isa_allocation(t_data *data)// tmp
{
	data->isa.n_registers = 16;
	data->isa.n_flags = 6;

	data->isa.bitfield_lengths.len = 3;
	data->isa.bitfield_lengths.arr = malloc(data->isa.bitfield_lengths.len * sizeof(t_parr));
	((t_parr *)data->isa.bitfield_lengths.arr)[0].len = 2;
	((t_parr *)data->isa.bitfield_lengths.arr)[0].arr =
		malloc(((t_parr *)data->isa.bitfield_lengths.arr)[0].len * sizeof(size_t));
	((t_parr *)data->isa.bitfield_lengths.arr)[1].len = 4;
	((t_parr *)data->isa.bitfield_lengths.arr)[1].arr =
		malloc(((t_parr *)data->isa.bitfield_lengths.arr)[1].len * sizeof(size_t));
	((t_parr *)data->isa.bitfield_lengths.arr)[2].len = 3;
	((t_parr *)data->isa.bitfield_lengths.arr)[2].arr =
		malloc(((t_parr *)data->isa.bitfield_lengths.arr)[2].len * sizeof(size_t));
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[0].arr)[0] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[0].arr)[1] = 24;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[1].arr)[0] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[1].arr)[1] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[1].arr)[2] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[1].arr)[3] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[2].arr)[0] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[2].arr)[1] = 8;
	((size_t *)((t_parr *)data->isa.bitfield_lengths.arr)[2].arr)[2] = 16;

	data->isa.formats.len = 6;
	data->isa.formats.arr = malloc(data->isa.formats.len * sizeof(t_format));
	((t_format *)data->isa.formats.arr)[0].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[0];
	((t_format *)data->isa.formats.arr)[0].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[0].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[0].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[0].bitfield_types.len * sizeof(t_bitfield_type));
	((t_format *)data->isa.formats.arr)[1].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[1];
	((t_format *)data->isa.formats.arr)[1].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[1].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[1].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[1].bitfield_types.len * sizeof(t_bitfield_type));
	((t_format *)data->isa.formats.arr)[2].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[1];
	((t_format *)data->isa.formats.arr)[2].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[2].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[2].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[2].bitfield_types.len * sizeof(t_bitfield_type));
	((t_format *)data->isa.formats.arr)[3].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[2];
	((t_format *)data->isa.formats.arr)[3].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[3].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[3].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[3].bitfield_types.len * sizeof(t_bitfield_type));
	((t_format *)data->isa.formats.arr)[4].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[2];
	((t_format *)data->isa.formats.arr)[4].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[4].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[4].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[4].bitfield_types.len * sizeof(t_bitfield_type));
	((t_format *)data->isa.formats.arr)[5].bitfield_lengths = &((t_parr *)data->isa.bitfield_lengths.arr)[2];
	((t_format *)data->isa.formats.arr)[5].bitfield_types.len =
		((t_format *)data->isa.formats.arr)[5].bitfield_lengths->len;
	((t_format *)data->isa.formats.arr)[5].bitfield_types.arr =
		malloc(((t_format *)data->isa.formats.arr)[5].bitfield_types.len * sizeof(t_bitfield_type));
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[0].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[0].bitfield_types.arr)[1] = UNUSED;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[1].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[1].bitfield_types.arr)[1] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[1].bitfield_types.arr)[2] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[1].bitfield_types.arr)[3] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[2].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[2].bitfield_types.arr)[1] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[2].bitfield_types.arr)[2] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[2].bitfield_types.arr)[3] = UNUSED;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[3].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[3].bitfield_types.arr)[1] = REGISTER;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[3].bitfield_types.arr)[2] = IMMEDIATE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[4].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[4].bitfield_types.arr)[1] = CONDITION;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[4].bitfield_types.arr)[2] = IMMEDIATE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[5].bitfield_types.arr)[0] = OPCODE;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[5].bitfield_types.arr)[1] = UNUSED;
	((t_bitfield_type *)((t_format *)data->isa.formats.arr)[5].bitfield_types.arr)[2] = IMMEDIATE;

	data->isa.instructions.len = 27;
	data->isa.instructions.arr = malloc(data->isa.instructions.len * sizeof(t_instruction));
	((t_instruction *)data->isa.instructions.arr)[0].opcode = 0;
	((t_instruction *)data->isa.instructions.arr)[0].format = &((t_format *)data->isa.formats.arr)[0];
	((t_instruction *)data->isa.instructions.arr)[1].opcode = 1;
	((t_instruction *)data->isa.instructions.arr)[1].format = &((t_format *)data->isa.formats.arr)[0];
	((t_instruction *)data->isa.instructions.arr)[2].opcode = 2;
	((t_instruction *)data->isa.instructions.arr)[2].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[3].opcode = 3;
	((t_instruction *)data->isa.instructions.arr)[3].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[4].opcode = 4;
	((t_instruction *)data->isa.instructions.arr)[4].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[5].opcode = 5;
	((t_instruction *)data->isa.instructions.arr)[5].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[6].opcode = 6;
	((t_instruction *)data->isa.instructions.arr)[6].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[7].opcode = 7;
	((t_instruction *)data->isa.instructions.arr)[7].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[8].opcode = 8;
	((t_instruction *)data->isa.instructions.arr)[8].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[9].opcode = 9;
	((t_instruction *)data->isa.instructions.arr)[9].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[10].opcode = 10;
	((t_instruction *)data->isa.instructions.arr)[10].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[11].opcode = 11;
	((t_instruction *)data->isa.instructions.arr)[11].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[12].opcode = 12;
	((t_instruction *)data->isa.instructions.arr)[12].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[13].opcode = 13;
	((t_instruction *)data->isa.instructions.arr)[13].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[14].opcode = 14;
	((t_instruction *)data->isa.instructions.arr)[14].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[15].opcode = 15;
	((t_instruction *)data->isa.instructions.arr)[15].format = &((t_format *)data->isa.formats.arr)[1];
	((t_instruction *)data->isa.instructions.arr)[16].opcode = 16;
	((t_instruction *)data->isa.instructions.arr)[16].format = &((t_format *)data->isa.formats.arr)[3];
	((t_instruction *)data->isa.instructions.arr)[17].opcode = 17;
	((t_instruction *)data->isa.instructions.arr)[17].format = &((t_format *)data->isa.formats.arr)[3];
	((t_instruction *)data->isa.instructions.arr)[18].opcode = 18;
	((t_instruction *)data->isa.instructions.arr)[18].format = &((t_format *)data->isa.formats.arr)[5];
	((t_instruction *)data->isa.instructions.arr)[19].opcode = 19;
	((t_instruction *)data->isa.instructions.arr)[19].format = &((t_format *)data->isa.formats.arr)[4];
	((t_instruction *)data->isa.instructions.arr)[20].opcode = 20;
	((t_instruction *)data->isa.instructions.arr)[20].format = &((t_format *)data->isa.formats.arr)[5];
	((t_instruction *)data->isa.instructions.arr)[21].opcode = 21;
	((t_instruction *)data->isa.instructions.arr)[21].format = &((t_format *)data->isa.formats.arr)[0];
	((t_instruction *)data->isa.instructions.arr)[22].opcode = 22;
	((t_instruction *)data->isa.instructions.arr)[22].format = &((t_format *)data->isa.formats.arr)[2];
	((t_instruction *)data->isa.instructions.arr)[23].opcode = 23;
	((t_instruction *)data->isa.instructions.arr)[23].format = &((t_format *)data->isa.formats.arr)[2];
	((t_instruction *)data->isa.instructions.arr)[24].opcode = 24;
	((t_instruction *)data->isa.instructions.arr)[24].format = &((t_format *)data->isa.formats.arr)[2];
	((t_instruction *)data->isa.instructions.arr)[25].opcode = 25;
	((t_instruction *)data->isa.instructions.arr)[25].format = &((t_format *)data->isa.formats.arr)[2];
	((t_instruction *)data->isa.instructions.arr)[26].opcode = 3;
	((t_instruction *)data->isa.instructions.arr)[26].format = &((t_format *)data->isa.formats.arr)[2];

	data->isa.flags.len = 6;
	data->isa.flags.arr = malloc(data->isa.flags.len * sizeof(size_t));
	((size_t *)data->isa.flags.arr)[0] = 0;
	((size_t *)data->isa.flags.arr)[1] = 1;
	((size_t *)data->isa.flags.arr)[2] = 2;
	((size_t *)data->isa.flags.arr)[3] = 3;
	((size_t *)data->isa.flags.arr)[4] = 4;
	((size_t *)data->isa.flags.arr)[5] = 5;

	data->isa.mnemonics.len = 33;
	data->isa.mnemonics.arr = malloc(data->isa.mnemonics.len * sizeof(t_mnemonic));
	((t_mnemonic *)data->isa.mnemonics.arr)[0].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[0].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[0]);
	((t_mnemonic *)data->isa.mnemonics.arr)[0].mnemonic = alloc_arr("NOP", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[1].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[1].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[1]);
	((t_mnemonic *)data->isa.mnemonics.arr)[1].mnemonic = alloc_arr("HLT", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[2].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[2].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[2]);
	((t_mnemonic *)data->isa.mnemonics.arr)[2].mnemonic = alloc_arr("ADD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[3].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[3].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[3]);
	((t_mnemonic *)data->isa.mnemonics.arr)[3].mnemonic = alloc_arr("SUB", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[4].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[4].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[4]);
	((t_mnemonic *)data->isa.mnemonics.arr)[4].mnemonic = alloc_arr("MUL", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[5].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[5].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[5]);
	((t_mnemonic *)data->isa.mnemonics.arr)[5].mnemonic = alloc_arr("DIV", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[6].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[6].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[6]);
	((t_mnemonic *)data->isa.mnemonics.arr)[6].mnemonic = alloc_arr("MOD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[7].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[7].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[7]);
	((t_mnemonic *)data->isa.mnemonics.arr)[7].mnemonic = alloc_arr("EXP", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[8].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[8].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[8]);
	((t_mnemonic *)data->isa.mnemonics.arr)[8].mnemonic = alloc_arr("AND", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[9].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[9].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[9]);
	((t_mnemonic *)data->isa.mnemonics.arr)[9].mnemonic = alloc_arr("OR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[10].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[10].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[10]);
	((t_mnemonic *)data->isa.mnemonics.arr)[10].mnemonic = alloc_arr("XOR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[11].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[11].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[11]);
	((t_mnemonic *)data->isa.mnemonics.arr)[11].mnemonic = alloc_arr("LBS", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[12].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[12].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[12]);
	((t_mnemonic *)data->isa.mnemonics.arr)[12].mnemonic = alloc_arr("RBS", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[13].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[13].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[13]);
	((t_mnemonic *)data->isa.mnemonics.arr)[13].mnemonic = alloc_arr("NAND", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[14].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[14].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[14]);
	((t_mnemonic *)data->isa.mnemonics.arr)[14].mnemonic = alloc_arr("NOR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[15].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[15].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[15]);
	((t_mnemonic *)data->isa.mnemonics.arr)[15].mnemonic = alloc_arr("XNOR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[16].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[16].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[16]);
	((t_mnemonic *)data->isa.mnemonics.arr)[16].mnemonic = alloc_arr("ILD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[17].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[17].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[17]);
	((t_mnemonic *)data->isa.mnemonics.arr)[17].mnemonic = alloc_arr("IADD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[18].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[18].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[18]);
	((t_mnemonic *)data->isa.mnemonics.arr)[18].mnemonic = alloc_arr("JMP", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[19].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[19].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[19]);
	((t_mnemonic *)data->isa.mnemonics.arr)[19].mnemonic = alloc_arr("BRH", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[20].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[20].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[20]);
	((t_mnemonic *)data->isa.mnemonics.arr)[20].mnemonic = alloc_arr("CAL", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[21].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[21].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[21]);
	((t_mnemonic *)data->isa.mnemonics.arr)[21].mnemonic = alloc_arr("RET", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[22].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[22].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[22]);
	((t_mnemonic *)data->isa.mnemonics.arr)[22].mnemonic = alloc_arr("LOD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[23].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[23].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[23]);
	((t_mnemonic *)data->isa.mnemonics.arr)[23].mnemonic = alloc_arr("STR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[24].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[24].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[24]);
	((t_mnemonic *)data->isa.mnemonics.arr)[24].mnemonic = alloc_arr("PLOD", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[25].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[25].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[25]);
	((t_mnemonic *)data->isa.mnemonics.arr)[25].mnemonic = alloc_arr("PSTR", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[26].type = INSTRUCTION;
	((t_mnemonic *)data->isa.mnemonics.arr)[26].compilation_target = &(((t_instruction *)data->isa.instructions.arr)[26]);
	((t_mnemonic *)data->isa.mnemonics.arr)[26].mnemonic = alloc_arr("CMP", NULL);
	((t_mnemonic *)data->isa.mnemonics.arr)[27].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[27].compilation_target = &(((size_t *)data->isa.flags.arr)[0]);
	((t_mnemonic *)data->isa.mnemonics.arr)[27].mnemonic = alloc_arr("s", "sign");
	((t_mnemonic *)data->isa.mnemonics.arr)[28].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[28].compilation_target = &(((size_t *)data->isa.flags.arr)[1]);
	((t_mnemonic *)data->isa.mnemonics.arr)[28].mnemonic = alloc_arr("ns", "notsign");
	((t_mnemonic *)data->isa.mnemonics.arr)[29].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[29].compilation_target = &(((size_t *)data->isa.flags.arr)[2]);
	((t_mnemonic *)data->isa.mnemonics.arr)[29].mnemonic = alloc_arr("ev", "even");
	((t_mnemonic *)data->isa.mnemonics.arr)[30].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[30].compilation_target = &(((size_t *)data->isa.flags.arr)[3]);
	((t_mnemonic *)data->isa.mnemonics.arr)[30].mnemonic = alloc_arr("nev", "noteven");
	((t_mnemonic *)data->isa.mnemonics.arr)[31].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[31].compilation_target = &(((size_t *)data->isa.flags.arr)[4]);
	((t_mnemonic *)data->isa.mnemonics.arr)[31].mnemonic = alloc_arr("z", "zero");
	((t_mnemonic *)data->isa.mnemonics.arr)[32].type = FLAG;
	((t_mnemonic *)data->isa.mnemonics.arr)[32].compilation_target = &(((size_t *)data->isa.flags.arr)[5]);
	((t_mnemonic *)data->isa.mnemonics.arr)[32].mnemonic = alloc_arr("nz", "notzero");
	return (0);
}

static size_t	count_opwords(t_parr* type)
{
	size_t	i = 0, n_opwords = 0;
	while (i < type->len)
	{
		if (((t_bitfield_type *)type->arr)[i] != UNUSED)
			n_opwords++;
		i++;
	}
	return (n_opwords);
}

static void	set_opwords(t_isa* isa)
{
	size_t	i = 0;
	while (i < isa->formats.len)
	{
		((t_format *)isa->formats.arr)[i].n_opwords
			= count_opwords(&((t_format *)isa->formats.arr)[i].bitfield_types);
		i++;
	}
}

bool	isa_loading(t_data* data)
{
	isa_allocation(data);// tmp
	set_opwords(&data->isa);
	return (0);
}
