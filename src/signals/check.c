#include <string.h>
#include "signals.h"
#include "error.h"

static bool	check_types(const cJSON *blueprint)
{
	if (cJSON_HasObjectItem(blueprint, JSON_TYPES) == 0)
		return (0);
	const cJSON	*types = cJSON_GetObjectItemCaseSensitive(blueprint, JSON_TYPES);
	if (cJSON_IsArray(types) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_TYPES, ERROR_JSON_NOT_ARRAY);
		return (1);
	}
	bool	error = 0;
	size_t	i_type = 0;
	const cJSON	*type;
	cJSON_ArrayForEach(type, types)
	{
		if (cJSON_IsString(type) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_TYPES, i_type,
				ERROR_JSON_NOT_STRING);
			error = 1;
		}
		i_type++;
	}
	return (error);
}

static bool	check_qualities(const cJSON *blueprint)
{
	if (cJSON_HasObjectItem(blueprint, JSON_QUALITIES) == 0)
		return (0);
	const cJSON	*qualities = cJSON_GetObjectItemCaseSensitive(blueprint, JSON_QUALITIES);
	if (cJSON_IsArray(qualities) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_QUALITIES, ERROR_JSON_NOT_ARRAY);
		return (1);
	}
	bool	error = 0;
	size_t	i_quality = 0;
	const cJSON	*quality;
	cJSON_ArrayForEach(quality, qualities)
	{
		if (cJSON_IsString(quality) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_QUALITIES, i_quality,
				ERROR_JSON_NOT_STRING);
			error = 1;
		}
		i_quality++;
	}
	return (error);
}

static bool	check_signals(const cJSON *blueprint)
{
	if (cJSON_HasObjectItem(blueprint, JSON_SIGNALS) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, ERROR_JSON_MISSING_ITEM);
		return (1);
	}
	const cJSON	*signals = cJSON_GetObjectItemCaseSensitive(blueprint, JSON_SIGNALS);
	if (cJSON_IsArray(signals) == 0)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, ERROR_JSON_NOT_ARRAY);
		return (1);
	}
	bool	error = 0;
	size_t	i_signal = 0;
	const cJSON	*signal;
	cJSON_ArrayForEach(signal, signals)
	{
		if (cJSON_IsObject(signal) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu)): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal,
				ERROR_JSON_NOT_ARRAY);
			error = 1;
			i_signal++;
			continue;
		}
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_NAME) == 0)
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal,
				JSON_SIGNAL_NAME, ERROR_JSON_MISSING_ITEM);
			error = 1;
		}
		else
		{
			const cJSON	*name = cJSON_GetObjectItemCaseSensitive(signal,
				JSON_SIGNAL_NAME);
			if (cJSON_IsString(name) == 0)
			{
				fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal,
					JSON_SIGNAL_NAME, ERROR_JSON_NOT_STRING);
				error = 1;
			}
		}
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_TYPE) != 0)
		{
			const cJSON	*type = cJSON_GetObjectItemCaseSensitive(signal,
				JSON_SIGNAL_TYPE);
			if (cJSON_IsString(type) == 0)
			{
				fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
					EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal,
					JSON_SIGNAL_TYPE, ERROR_JSON_NOT_STRING);
				error = 1;
			}
		}
		i_signal++;
	}
	if (i_signal < 1)
	{
		fprintf(stderr, "%s: %s (\"%s\"): %s (must contain at least 1)\n",
			EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, ERROR_JSON_TOO_FEW_ITEMS);
		return (1);
	}
	return (error);
}

static bool	check_signals_type(const cJSON *blueprint)
{
	if (cJSON_HasObjectItem(blueprint, JSON_SIGNALS) == 0)
		return (0);
	const cJSON	*types, *signals = cJSON_GetObjectItemCaseSensitive(blueprint,
		JSON_SIGNALS);
	if (cJSON_IsArray(signals) == 0)
		return (0);
	if (cJSON_HasObjectItem(blueprint, JSON_TYPES) != 0
		&& cJSON_IsArray(cJSON_GetObjectItemCaseSensitive(blueprint, JSON_TYPES)) != 0)
		types = cJSON_GetObjectItemCaseSensitive(blueprint, JSON_TYPES);
	else
		types = NULL;
	size_t	i_signal = 0;
	bool	error = 0;
	const cJSON	*signal;
	cJSON_ArrayForEach(signal, signals)
	{
		i_signal++;
		if (cJSON_HasObjectItem(signal, JSON_SIGNAL_TYPE) == 0)
			continue;
		const cJSON	*signal_type = cJSON_GetObjectItemCaseSensitive(signal,
			JSON_SIGNAL_TYPE);
		if (cJSON_IsString(signal_type) == 0)
			continue;
		if (types == NULL)
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal - 1,
				JSON_SIGNAL_TYPE, ERROR_JSON_INVALID_TYPE);
			error = 1;
			continue;
		}
		const char	*str_signal_type = cJSON_GetStringValue(signal_type);
		size_t	i_type = 0;
		const cJSON	*type;
		cJSON_ArrayForEach(type, types)
		{
			if (cJSON_IsString(type) != 0
				&& strcmp(cJSON_GetStringValue(type), str_signal_type) == 0)
				break ;
			i_type++;
		}
		if (i_type == (size_t)cJSON_GetArraySize(types))
		{
			fprintf(stderr, "%s: %s (\"%s\" (index %zu): \"%s\"): %s\n",
				EXECUTABLE_NAME, ERROR_JSON_SYNTAX, JSON_SIGNALS, i_signal - 1,
				JSON_SIGNAL_TYPE, ERROR_JSON_INVALID_TYPE);
			error = 1;
		}
	}
	return (error);
}

bool	check_blueprint_syntax(const cJSON *blueprint)
{
	bool	error = 0;
	if (check_types(blueprint) == 1)
		error = 1;
	if (check_qualities(blueprint) == 1)
		error = 1;
	if (check_signals(blueprint) == 1)
		error = 1;
	if (check_signals_type(blueprint) == 1)
		error = 1;
	return (error);
}
