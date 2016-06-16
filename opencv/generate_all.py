# -*- coding: utf-8 -*-

import generator
import cvcalib3d
import cvcore
import cvimgproc

generator.generatePackageFiles(cvcalib3d.package)
generator.generatePackageFiles(cvcore.package) 
generator.generatePackageFiles(cvimgproc.package)