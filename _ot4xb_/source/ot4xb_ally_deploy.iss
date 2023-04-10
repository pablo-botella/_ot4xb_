#define ot4xbBuildsFolder       "."
#define ot4xbVersion            "001_007_000_005"
#define ot4xbDotVersion         "1.7.0.5"
#define recreateprojectFolder   "V:\allycpp\_ot4xb_"
#define appsLibraryFolder       "V:\allyapps\library\ot4xb"
#define appsLibraryZIPsFolder   "V:\allyapps\library\ot4xb\ZIPs"
#define copyFlags               "ignoreversion"
                                                                      
[Setup]

AppName = ot4xb ally {#ot4xbDotVersion}
AppVersion = {#ot4xbDotVersion}
Uninstallable = no          
CreateUninstallRegKey = no
DefaultDirName= {#recreateprojectFolder}
OutputBaseFilename= ot4xb_{#ot4xbVersion}_ally_setup
OutputDir=.







                                                                   

[Dirs]
Name: "{#recreateprojectFolder}"
Name: "{#recreateprojectFolder}\builds"
Name: "{#recreateprojectFolder}\source"
Name: "{#recreateprojectFolder}\builds\_ot4xb_{#ot4xbVersion}"
Name: "{#recreateprojectFolder}\builds\_ot4xb_{#ot4xbVersion}_source"
Name: "{#appsLibraryFolder}"
Name: "{#appsLibraryZIPsFolder}"
                                                                      
                                                                      
                                                                      

[Files]
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}.zip;               DestDir: {#recreateprojectFolder}\builds;                                  Flags: {#copyFlags}
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}_source.zip;        DestDir: {#recreateprojectFolder}\builds;                                  Flags: {#copyFlags}
                                                                                                                                             
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}.zip;               DestDir: {#appsLibraryZIPsFolder};                                         Flags: {#copyFlags}
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}_source.zip;        DestDir: {#appsLibraryZIPsFolder};                                         Flags: {#copyFlags}

Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}\*.*;               DestDir: {#recreateprojectFolder}\builds\_ot4xb_{#ot4xbVersion};           Flags: {#copyFlags} recursesubdirs
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}_source\*.*;        DestDir: {#recreateprojectFolder}\builds\_ot4xb_{#ot4xbVersion}_source;    Flags: {#copyFlags} recursesubdirs

Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}_source\ot4xb.sln;   DestDir: {#recreateprojectFolder};                                        Flags: {#copyFlags}
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}_source\source\*.*;  DestDir: {#recreateprojectFolder}\source;                                 Flags: {#copyFlags} recursesubdirs

Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}\*.*;                DestDir: {#appsLibraryFolder};                                            Flags: {#copyFlags}
Source: {#ot4xbBuildsFolder}\_ot4xb_{#ot4xbVersion}\include\*.*;        DestDir: {#appsLibraryFolder};                                            Flags: {#copyFlags}


                                                                                  
                                                                                  
