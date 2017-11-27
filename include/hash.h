struct entry_s {
	char *key;
	char *data;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashmap_s {
	int size;
	struct entry_s **map;
	int count;
};

typedef struct hashmap_s hashmap_t;

hashmap_t *hm_create(int size);
entry_t *newentry(char *key, char *data);
int hash(hashmap_t *hashmap, char *key);
void deletemap(hashmap_t *hashmap);
void hm_insert(hashmap_t *hashmap, char *key, char *data);
void expandhashmap(hashmap_t *hm, int newsize);
void hm_set(hashmap_t *hashmap, char *key, char *data);
char *hm_get(hashmap_t *hashmap, char *key);