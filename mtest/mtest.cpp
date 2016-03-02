//=============================================================================
//  MuseScore
//  Music Composition & Notation
//
//  Copyright (C) 2012 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#include <stdio.h>
#include "all.h"

// static QFile log;
static int processed = 0;
static int failed = 0;

const char* tests[] = {
#if 0
      "guitarpro/tst_guitarpro",
      "biab/tst_biab",
      "testoves/structure/tst_ove_structure",
      "testoves/ove3/tst_ove_ove3",
      "testoves/bdat/tst_ove_bdat",
      "capella/io/tst_capella_io",
      "importmidi/tst_importmidi",
      "musicxml/io/tst_mxml_io",
#endif

      "libmscore/selectionrangedelete/tst_selectionrangedelete",
      "libmscore/layout/tst_benchmark",
      "libmscore/compat/tst_compat",
      "libmscore/clef_courtesy/tst_clef_courtesy",
      "libmscore/instrumentchange/tst_instrumentchange",
      "libmscore/barline/tst_barline",
      "libmscore/clef/tst_clef",
      "libmscore/timesig/tst_timesig",
      "libmscore/repeat/tst_repeat",
      "libmscore/dynamic/tst_dynamic",
      "libmscore/midimapping/tst_midimapping",
      "libmscore/breath/tst_breath",
      "libmscore/tuplet/tst_tuplet",
      "libmscore/join/tst_join",
      "libmscore/copypaste/tst_copypaste",
      "libmscore/parts/tst_parts",
      "libmscore/transpose/tst_transpose",
      "libmscore/hairpin/tst_hairpin",
      "libmscore/concertpitch/tst_concertpitchbenchmark",
      "libmscore/element/tst_element",
      "libmscore/selectionfilter/tst_selectionfilter",
      "libmscore/earlymusic/tst_earlymusic",

      "libmscore/note/tst_note",
      "libmscore/keysig/tst_keysig",
//      "libmscore/midi/tst_midi",
//      "libmscore/tools/tst_tools",
//      "libmscore/splitstaff/tst_splitstaff",
#if 0
      "libmscore/chordsymbol/tst_chordsymbol",
      "libmscore/split/tst_split",
      "libmscore/beam/tst_beam",
      "libmscore/spanners/tst_spanners",
      "libmscore/plugins/tst_plugins",
      "libmscore/measure/tst_measure",
      "libmscore/album/tst_album",
      "libmscore/text/tst_text",
      "libmscore/copypastesymbollist/tst_copypastesymbollist",
      "scripting/tst_scripting"
#endif
      };

//---------------------------------------------------------
//   process
//---------------------------------------------------------

static void process(const QString& cmd)
      {
      QStringList args;
      int rv = QProcess::execute(cmd, args);
      if (rv != 0)
            failed++;
      processed++;
      }

//---------------------------------------------------------
//   scanDir
//---------------------------------------------------------

static void scanDir(QDir d)
      {
      QFileInfoList l = d.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Dirs);
      foreach(const QFileInfo& fi, l) {
            if (fi.isDir()) {
                  scanDir(QDir(fi.filePath()));
                  }
            else if (fi.isExecutable()) {
                  QString s(fi.filePath());
                  if (fi.completeBaseName().startsWith("tst_"))
                        process(s);
                  }
            }
      }

//---------------------------------------------------------
//   main
//---------------------------------------------------------

int main(int argc, char* argv[])
      {
#if 0
      log.setFileName("mtest.log");
      if (!log.open(QIODevice::WriteOnly)) {
            fprintf(stderr, "mtest: cannot open log file <mtest.log>\n");
            exit(-1);
            }
#endif
      QDir wd(QDir::current());
#ifdef Q_OS_MAC
      wd.cdUp();
#endif

#if 0
      scanDir(wd);
#else
      for (const char* s : tests)
            process(s);
#endif

      printf("\n");
      printf("================\n");
      printf("  processed %d  -- failed %d\n", processed, failed);
      printf("================\n");
      return 0;
      }

