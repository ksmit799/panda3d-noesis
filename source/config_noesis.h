#ifndef CONFIG_NOESIS_H
#define CONFIG_NOESIS_H

#include "pandabase.h"

#include "dconfig.h"
#include "notifyCategoryProxy.h"

#define EXPCL_NOESIS EXPORT_CLASS
#define EXPTP_NOESIS EXPORT_TEMPL

ConfigureDecl(config_noesis, EXPORT_CLASS, EXPORT_TEMPL);
NotifyCategoryDecl(noesis, EXPORT_CLASS, EXPORT_TEMPL);

extern EXPCL_NOESIS void init_libnoesis();

#endif // CONFIG_NOESIS_H
