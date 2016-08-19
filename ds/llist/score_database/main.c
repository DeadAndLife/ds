#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <llist.h>
#include <debug.h>

#define NAMESIZE 32
#define BUFSIZE 4

#define EXIT (EOF - 1)

struct score {
      int id;
      char name[NAMESIZE];
      int chinese;
      int math;
};

static LLIST *database = NULL;

enum {ADD, DEL, FIND, SAVE, LOAD, UNKNOWN};

static void notice(void)
{
      printf("enter a cmd:\n");
}

static int id_cmp(const void *p1, const void *p2)
{
      const struct score *data = p1;
      const int *id = p2;

      return data->id - *id;
}

static char *ym_gets(void)
{
      char buf[BUFSIZE];
      char *s = NULL, *tmp;
      int len = 0;

      s = malloc(1);
      *s = '\0';
      while (1) {
	    fgets(buf, BUFSIZE, stdin);
	    tmp = realloc(s, len + strlen(buf) + 1);
	    if (tmp == NULL) {
		  free(s);
		  return NULL;
	    }
	    s = tmp;
	    strcat(s, buf);
	    len = strlen(s);
	    if (s[len - 1] == '\n') {
		  s[len - 1] = '\0';
		  return s;
	    }
      }
}

int exec_cmd(const char *cmd);
static void _add_notice(void);
static void _add(void);
static void _del_notice(void);
static void _del(void);
static void _find_notice(void);
static void _find(void);
static void _save_notice(void);
static void _save(void);
static void _load_notice(void);
static void _load(void);

int main(void)
{
      char *cmd;
      int ret;
      database = llist_creat(sizeof(struct score));
      if (database == NULL) {
	    fprintf(stderr, "memory shortage.\n");
	    exit(1);
      }

      while (1) {
	    notice();
	    cmd = ym_gets();
	    ret = exec_cmd(cmd);
	    if (ret == EXIT) {
		  free(cmd);
		  break;
	    }
	    free(cmd);
      }

      llist_destroy(database);
      return 0;
}

static int get_cmd(const char *cmd)
{
      int i;

      myprintf3("in get_cmd:");
      myprintf3(cmd);
      myprintf3("\n");

      for (i = 0; isalpha(cmd[i]); i++)
	    ;
      if (!strncmp(cmd, "add", i)) {
	    return ADD;
      } else if (!strncmp(cmd, "del", i)) {
	    return DEL;
      } else if (!strncmp(cmd, "find", i)) {
	    return FIND;
      } else if (!strncmp(cmd, "save", i)) {
	    return SAVE;
      } else if (!strncmp(cmd, "load", i)) {
	    return LOAD;
      } else if (!strncmp(cmd, "exit", i)) {
	    return EXIT;
      }

      return UNKNOWN;
}

int exec_cmd(const char *cmd)
{
      int command = get_cmd(cmd);

      switch (command) {
      case ADD:
	    _add();
	    break;
      case DEL:
	    _del();
	    break;
      case FIND:
	    _find();
	    break;
      case SAVE:
	    _save();
	    break;
      case LOAD:
	    _load();
	    break;
      case EXIT:
	    return EXIT;
	    break;
      default:
	    return UNKNOWN;
	    break;
      }

      return 0;
}

static void _add_notice(void)
{
      printf("enter a record:\n");
}

static void _add(void)
{
      char *buf;
      struct score new;
      struct score *record;

      _add_notice();
      buf = ym_gets();

      sscanf(buf, "%d %s %d %d", \
	     &new.id, new.name, \
	     &new.chinese, &new.math);

      record = llist_find(database, &new.id, id_cmp);
      if (record == NULL) {
	    llist_prepend(database, &new);
      } else {
	    strncpy(record->name, new.name, NAMESIZE);
	    record->chinese = new.chinese;
	    record->math = new.math;
      }

      free(buf);
}

static void _del_notice(void)
{
      printf("enter a id:\n");
}

static void _del(void)
{
      char buf[BUFSIZE];
      int id;

      _del_notice();
      fgets(buf, BUFSIZE, stdin);
      if (0) {

      }
      sscanf(buf, "%d", &id);

      llist_delet(database, &id, id_cmp);
}

static void _find_notice(void)
{
      printf("enter a id:\n");
}

static void _find(void)
{
      char buf[BUFSIZE];
      int id;
      struct score *record;

      _find_notice();
      fgets(buf, BUFSIZE, stdin);
      if (0) {

      }
      sscanf(buf, "%d", &id);

      record = llist_find(database, &id, id_cmp);
      if (record == NULL) {
	    printf("no this id.\n");
      } else {
	    printf("%d, %s, %d, %d\n", \
		   record->id, record->name, \
		   record->chinese, record->math);
      }
}

static void _save_notice(void)
{
      printf("enter path:\n");
}

static void _save(void)
{
      FILE *fp;
      char *path;

      _save_notice();
      path = ym_gets();
      fp = fopen(path, "w");
      llist_save(database, fp);
      fclose(fp);
      free(path);
}

static void _load_notice(void)
{
      printf("enter path:\n");
}

static void _load(void)
{
      FILE *fp;
      char *path;

      _load_notice();
      path = ym_gets();
      fp = fopen(path, "r");
      llist_destroy(database);
      database = llist_load(fp);
      fclose(fp);
      free(path);
}

