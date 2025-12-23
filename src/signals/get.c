#include <stdlib.h>
#include <string.h>
#include "parr.h"
#include "pstr.h"
#include "blueprint.h"
#include "signals.h"

static bool	get_types(blueprint_t *blueprint, const cJSON *types)
{
	if (cJSON_GetArraySize(types) == 0)
		return (0);
	blueprint->types.len = (size_t)cJSON_GetArraySize(types);
	blueprint->types.obj_size = sizeof(char *);
	blueprint->types.arr = malloc(blueprint->types.len * blueprint->types.obj_size);
	if (blueprint->types.arr == NULL)
	{
		blueprint->types.len = 0;
		return (1);
	}
	size_t	i_type = 0;
	const cJSON	*type;
	cJSON_ArrayForEach(type, types)
	{
		((char **)blueprint->types.arr)[i_type] = strdup(cJSON_GetStringValue(type));
		if (((char **)blueprint->types.arr)[i_type] == NULL)
		{
			blueprint->types.len = i_type + 1;
			return (1);
		}
		i_type++;
	}
	return (0);
}

static bool	get_qualities(blueprint_t *blueprint, const cJSON *qualities)
{
	if (cJSON_GetArraySize(qualities) == 0)
		return (0);
	blueprint->qualities.len = (size_t)cJSON_GetArraySize(qualities);
	blueprint->qualities.obj_size = sizeof(char *);
	blueprint->qualities.arr = malloc(blueprint->qualities.len * blueprint->qualities.obj_size);
	if (blueprint->qualities.arr == NULL)
	{
		blueprint->qualities.len = 0;
		return (1);
	}
	size_t	i_quality = 0;
	const cJSON	*quality;
	cJSON_ArrayForEach(quality, qualities)
	{
		((char **)blueprint->qualities.arr)[i_quality]
			= strdup(cJSON_GetStringValue(quality));
		if (((char **)blueprint->qualities.arr)[i_quality] == NULL)
		{
			blueprint->qualities.len = i_quality + 1;
			return (1);
		}
		i_quality++;
	}
	return (0);
}

static parr_t	init_counts(blueprint_t *blueprint, const cJSON *signals)
{
	parr_t	counts;
	counts.len = blueprint->types.len + 1;
	counts.obj_size = sizeof(size_t);
	counts.arr = calloc(counts.len, counts.obj_size);
	if (counts.arr == NULL)
		return ((parr_t){0});
	const cJSON	*signal;
	cJSON_ArrayForEach(signal, signals)
	{
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_TYPE) != 0)
		{
			const cJSON	*item_signal = cJSON_GetObjectItemCaseSensitive(signal,
				JSON_SIGNAL_TYPE);
			((size_t *)counts.arr)[get_i_type(&blueprint->types,
				cJSON_GetStringValue(item_signal)) + 1]++;
		}
		else
			((size_t *)counts.arr)[0]++;
	}
	size_t	count = ((size_t *)counts.arr)[0];
	((size_t *)counts.arr)[0] = 0;
	for (size_t i = 1; i < counts.len; i++)
	{
		size_t	swap = ((size_t *)counts.arr)[i];
		((size_t *)counts.arr)[i] = ((size_t *)counts.arr)[i - 1] + count;
		count = swap;
	}
	return (counts);
}

static bool	get_signals(blueprint_t *blueprint, const cJSON *signals)
{
	parr_t	counts = init_counts(blueprint, signals);
	blueprint->signals.len = (size_t)cJSON_GetArraySize(signals);
	blueprint->signals.obj_size = sizeof(signal_t);
	blueprint->signals.arr = calloc(blueprint->signals.len, blueprint->signals.obj_size);
	if (blueprint->signals.arr == NULL || counts.arr == NULL)
	{
		blueprint->signals.len = 0;
		free(counts.arr);
		return (1);
	}
	size_t	i_signal = 0, i_count;
	const cJSON	*signal;
	cJSON_ArrayForEach(signal, signals)
	{
		const cJSON	*item_signal;
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_TYPE) != 0)
		{
			item_signal = cJSON_GetObjectItemCaseSensitive(signal, JSON_SIGNAL_TYPE);
			i_count = (size_t)get_i_type(&blueprint->types,
				cJSON_GetStringValue(item_signal)) + 1;
		}
		else
			i_count = 0;
		size_t	i_insert = ((size_t *)counts.arr)[i_count];
		((size_t *)counts.arr)[i_count]++;
		item_signal = cJSON_GetObjectItemCaseSensitive(signal, JSON_SIGNAL_NAME);
		((signal_t *)blueprint->signals.arr)[i_insert].name
			= strdup(cJSON_GetStringValue(item_signal));
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_TYPE) != 0)
		{
			item_signal = cJSON_GetObjectItemCaseSensitive(signal, JSON_SIGNAL_TYPE);
			((signal_t *)blueprint->signals.arr)[i_insert].type
				= get_type(&blueprint->types, cJSON_GetStringValue(item_signal));
		}
		if (((signal_t *)blueprint->signals.arr)[i_insert].name == NULL)
		{
			free(counts.arr);
			return (1);
		}
		i_signal++;
	}
	free(counts.arr);
	return (0);
}

static bool	init_blueprint_text(blueprint_t *blueprint, pstr_t *input_name)
{
	if (blueprint->text[LABEL] == NULL)
		blueprint->text[LABEL] = strndup(input_name->str, input_name->len);
	if (blueprint->text[DESCRIPTION] == NULL)
		blueprint->text[DESCRIPTION] = strdup(JSON_BLUEPRINT_DESCRIPTION);
	return (blueprint->text[LABEL] == NULL || blueprint->text[DESCRIPTION] == NULL);
}

bool	init_blueprint(blueprint_t *blueprint, pstr_t *input_name, const cJSON *json_blueprint)
{
	if (init_blueprint_text(blueprint, input_name) == 1)
		return (1);
	const cJSON	*item_blueprint;
	if (cJSON_HasObjectItem(json_blueprint, JSON_TYPES) != 0)
	{
		item_blueprint = cJSON_GetObjectItemCaseSensitive(json_blueprint, JSON_TYPES);
		if (get_types(blueprint, item_blueprint) == 1)
			return (1);
	}
	if (cJSON_HasObjectItem(json_blueprint, JSON_QUALITIES) != 0)
	{
		item_blueprint = cJSON_GetObjectItemCaseSensitive(json_blueprint, JSON_QUALITIES);
		if (get_qualities(blueprint, item_blueprint) == 1)
			return (1);
	}
	item_blueprint = cJSON_GetObjectItemCaseSensitive(json_blueprint, JSON_SIGNALS);
	return (get_signals(blueprint, item_blueprint));
}
