#!/bin/bash

../bin/Generator
mv ../bin/db.cpp ../DAL
mv ../bin/db.h ../include
mv ../bin/TableImpls.cpp ../DAL
mv ../bin/TableImpls.h ../include
