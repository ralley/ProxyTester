#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <QString>
#include <pError.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <QFile>
#include <QTextStream>

int readFile(const QString &importPath, QString &str);
int writeFile(const QString &str);
#endif // CONFIG_H
