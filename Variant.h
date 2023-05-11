#ifndef VARIANT_HEADER
#define VARIANT_HEADER

#include <cstdlib>
#include <cstring>
enum VARIANT_DATA_TYPES {
  NULL_TYPE,
  VOID_TYPE,
  BOOL_TYPE,
  CHAR_TYPE,
  INTAGER_TYPE,
  SIGNED_INTAGER_TYPE,
  UNSIGNED_INTAGER_TYPE,
  FLOAT_TYPE,
  DOUBLE_TYPE,
  STRING_TYPE,
  DATE_TYPE,
};

char *variant_type_to_string(VARIANT_DATA_TYPES t) {
  char *name = (char*)malloc(sizeof(char) * 25);
  memset(name, 0, 25);

  switch (t) {
  case NULL_TYPE:
    strncpy(name, "null", 4);
    break;
  case VOID_TYPE:
    strncpy(name, "void", 4);
    break;
  case BOOL_TYPE:
    strncpy(name, "bool", 4);
    break;
  case CHAR_TYPE:
    strncpy(name, "char", 4);
    break;
  case INTAGER_TYPE:
    strncpy(name, "intager", 7);
    break;
  case SIGNED_INTAGER_TYPE:
    strncpy(name, "signed intager", 14);
    break;
  case UNSIGNED_INTAGER_TYPE:
    strncpy(name, "unsigned intager", 16);
    break;
  case FLOAT_TYPE:
      strncpy(name, "float", 5);
    break;
  case DOUBLE_TYPE:
      strncpy(name, "double", 6);
    break;
  }
  return name;
}

typedef VARIANT_DATA_TYPES VariantDataTypes;

struct S_VariantData {
  VariantDataTypes type;
  union {
    bool bool_v;
    char char_v;
    int int_v; // int, signed int, unsigned int with casting
    float float_v;
    double double_v;
    char *string_v;
  } value;
};

typedef S_VariantData VariantData;

#endif