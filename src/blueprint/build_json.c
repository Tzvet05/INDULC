#include <sys/param.h>
#include <stdint.h>
#include "point.h"
#include "data.h"
#include "signals.h"
#include "blueprint.h"

static int64_t	convert_instruction_number(data_t *data, size_t i_instruction)
{
	int64_t	buffer = 0;
	uint8_t	*ptr = (uint8_t *)data->output.machine_code.arr
		+ (i_instruction * data->output.machine_code.obj_size);
	for (size_t i_byte = 0; i_byte < data->output.machine_code.obj_size; i_byte++)
		buffer |= (((int64_t)(*(ptr + i_byte))) & 0x00000000000000FF)
			<< (((data->output.machine_code.obj_size - 1) - i_byte) * 8);
	return (buffer);
}

static bool	build_filter(data_t *data, cJSON *filters, size_t i_filter, size_t i_signal,
	size_t i_quality, size_t i_instruction)
{
	cJSON	*filter = cJSON_CreateObject();
	if (filter == NULL)
		return (1);
	cJSON_AddItemToArray(filters, filter);
	if (cJSON_AddNumberToObject(filter, JSON_INDEX, (double)(i_filter + 1)) == NULL
		|| cJSON_AddStringToObject(filter, JSON_NAME,
		((signal_t *)data->blueprint.signals.arr)[i_signal].name) == NULL)
		return (1);
	if (((signal_t *)data->blueprint.signals.arr)[i_signal].type != NULL
		&& cJSON_AddStringToObject(filter, JSON_TYPE,
		((signal_t *)data->blueprint.signals.arr)[i_signal].type) == NULL)
		return (1);
	if (data->blueprint.qualities.len > 0 && cJSON_AddStringToObject(filter, JSON_QUALITY,
		((char **)data->blueprint.qualities.arr)[i_quality]) == NULL)
		return (1);
	if (cJSON_AddStringToObject(filter, JSON_COMPARATOR, JSON_ENTITY_FILTER_COMPARATOR) == NULL)
		return (1);
	return (cJSON_AddNumberToObject(filter, JSON_COUNT,
		(double)convert_instruction_number(data, i_instruction)) == NULL);
}

static bool	build_filters(data_t *data, cJSON *section, size_t i_instruction)
{
	cJSON	*filters = cJSON_AddArrayToObject(section, JSON_FILTERS);
	if (filters == NULL)
		return (1);
	size_t	i_signal = 0, i_filter = 0;
	while (i_signal < data->blueprint.signals.len
		&& i_instruction < data->output.machine_code.len)
	{
		size_t	i_quality = 0;
		do
		{
			if (build_filter(data, filters, i_filter, i_signal, i_quality,
				i_instruction) == 1)
				return (1);
			i_instruction++;
			i_filter++;
			i_quality++;
		}
		while (i_quality < data->blueprint.qualities.len
			&& i_instruction < data->output.machine_code.len);
		i_signal++;
	}
	return (0);
}

static bool	build_entity(data_t *data, cJSON *entities, size_t i_entity, size_t i_instruction,
	point_t pos)
{
	cJSON	*entity = cJSON_CreateObject();
	if (entity == NULL)
		return (1);
	cJSON_AddItemToArray(entities, entity);
	if (cJSON_AddNumberToObject(entity, JSON_ENTITY_NUMBER, (double)(i_entity + 1)) == NULL
		|| cJSON_AddStringToObject(entity, JSON_NAME,
		JSON_ITEM_CONSTANT_COMBINATOR) == NULL)
		return (1);
	cJSON	*position = cJSON_AddObjectToObject(entity, JSON_POSITION);
	if (position == NULL
		|| cJSON_AddNumberToObject(position, JSON_X, (double)pos.x) == NULL
		|| cJSON_AddNumberToObject(position, JSON_Y, (double)pos.y) == NULL)
		return (1);
	if (cJSON_AddNumberToObject(entity, JSON_DIRECTION, JSON_ENTITY_DIRECTION) == NULL)
		return (1);
	cJSON	*control_behavior = cJSON_AddObjectToObject(entity, JSON_CONTROL_BEHAVIOR);
	if (control_behavior == NULL)
		return (1);
	cJSON	*sections = cJSON_AddObjectToObject(control_behavior, JSON_SECTIONS);
	if (sections == NULL)
		return (1);
	cJSON	*arr_sections = cJSON_AddArrayToObject(sections, JSON_SECTIONS);
	if (arr_sections == NULL)
		return (1);
	cJSON	*section = cJSON_CreateObject();
	if (section == NULL)
		return (1);
	cJSON_AddItemToArray(arr_sections, section);
	if (cJSON_AddNumberToObject(section, JSON_INDEX, JSON_ENTITY_SECTION_INDEX + 1) == NULL)
		return (1);
	return (build_filters(data, section, i_instruction));
}

static bool	build_entities(data_t *data, cJSON *blueprint)
{
	cJSON	*entities = cJSON_AddArrayToObject(blueprint, JSON_ENTITIES);
	if (entities == NULL)
		return (1);
	point_t	position = {0};
	size_t	instructions_per_entity = data->blueprint.signals.len
		* MAX(data->blueprint.qualities.len, 1);
	for (size_t i_entity = 0; i_entity < (data->output.machine_code.len
		+ (instructions_per_entity - 1)) / instructions_per_entity; i_entity++)
	{
		if (build_entity(data, entities, i_entity, i_entity * instructions_per_entity,
			position) == 1)
			return (1);
		position.y += 1;
	}
	return (0);
}

static bool	build_icon(cJSON *icons, size_t i_icon)
{
	cJSON	*icon = cJSON_CreateObject();
	if (icon == NULL)
		return (1);
	cJSON_AddItemToArray(icons, icon);
	cJSON	*signal = cJSON_AddObjectToObject(icon, JSON_SIGNAL);
	return (signal == NULL
		|| cJSON_AddStringToObject(signal, JSON_NAME, JSON_ITEM_CONSTANT_COMBINATOR) == NULL
		|| cJSON_AddNumberToObject(icon, JSON_INDEX, (double)(i_icon + 1)) == NULL);
}

static bool	build_icons(cJSON *blueprint)
{
	cJSON	*icons = cJSON_AddArrayToObject(blueprint, JSON_ICONS);
	if (icons == NULL)
		return (1);
	return (build_icon(icons, 0));
}

bool	build_json_blueprint(data_t *data)
{
	cJSON	*main_object = cJSON_CreateObject();
	if (main_object == NULL)
		return (1);
	cJSON	*blueprint = cJSON_AddObjectToObject(main_object, JSON_BLUEPRINT);
	if (blueprint == NULL
		|| cJSON_AddStringToObject(blueprint, JSON_DESCRIPTION,
		data->blueprint.text[DESCRIPTION]) == NULL
		|| build_icons(blueprint) == 1 || build_entities(data, blueprint) == 1
		|| cJSON_AddStringToObject(blueprint, JSON_ITEM, JSON_ITEM_BLUEPRINT) == NULL
		|| cJSON_AddStringToObject(blueprint, JSON_LABEL,
		data->blueprint.text[LABEL]) == NULL
		|| cJSON_AddNumberToObject(blueprint, JSON_VERSION, JSON_BLUEPRINT_VERSION) == NULL)
	{
		cJSON_Delete(main_object);
		return (1);
	}
	data->output.json = main_object;
	return (0);
}
