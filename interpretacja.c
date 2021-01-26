
#include "cos.h"

int decode_type(char *type)
{
    if (strcmp(type, "wall") == 0)
    {
        return 1;
    }
    else if (strcmp(type, "grass") == 0)
    {
        return 2;
    }
    else if (strcmp(type, "sand") == 0)
    {
        return 3;
    }
    return 0;
}

Dane *interpret_response(const char *const chunk, Dane *w)
{
    const cJSON *payload = NULL;
    cJSON *game_json = cJSON_Parse(chunk);
    if (game_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
    }
    else
    {
        payload = cJSON_GetObjectItemCaseSensitive(game_json, "payload");
        cJSON *current_x = cJSON_GetObjectItemCaseSensitive(payload, "current_x");
        cJSON *list = cJSON_GetObjectItemCaseSensitive(payload, "list");
        if (list != NULL)
        {
            cJSON *object = NULL;
            cJSON *_x = NULL;
            cJSON *_y = NULL;
            cJSON *_type = NULL;
            for (int i = 0; i < cJSON_GetArraySize(list); i++)
            {
                cJSON *subitem = cJSON_GetArrayItem(list, i);
                _x = cJSON_GetObjectItem(subitem, "x");
                _y = cJSON_GetObjectItem(subitem, "y");
                _type = cJSON_GetObjectItem(subitem, "type");
                w->y[i] = _x->valueint;
                w->x[i] = _y->valueint;
                w->field[i] = decode_type(_type->valuestring);
            }

            printf("koniec if(list...\n");
        }

        else if (current_x != NULL)
        {
            int s;
            cJSON *current_y = cJSON_GetObjectItemCaseSensitive(payload, "current_y");
            cJSON *field_type = cJSON_GetObjectItemCaseSensitive(payload, "field_type");
            cJSON *direction = cJSON_GetObjectItemCaseSensitive(payload, "direction");
            w->y[0] = current_x->valueint;
            w->x[0] = current_y->valueint;
            w->field[0] = decode_type(field_type->valuestring);
            w->kierunek_lufy = direction->valuestring[0];
            w->website_y = current_y->valueint;
            w->website_x = current_x->valueint;
        }
    }
    return w;
}