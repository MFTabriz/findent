  std::cout << "Usage of findent in gedit" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "1) as an external tool:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   Enter the following commands:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "#################################################" << std::endl;
  std::cout << "mkdir -p $HOME/bin" << std::endl;
  std::cout << "findent --gedit_external > $HOME/bin/findent-gedit" << std::endl;
  std::cout << "chmod +x $HOME/bin/findent-gedit" << std::endl;
  std::cout << "#################################################" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "   Make sure the $HOME/bin is in the PATH environment variable." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "    Open gedit:" << std::endl;
  std::cout << "    ----------------------- " << std::endl;
  std::cout << "       (Edit ->) Preferences -> plugins : enable \"External Tools\"" << std::endl;
  std::cout << "       Close gedit and start it again." << std::endl;
  std::cout << "       Tools -> Manage External Tools -> Add" << std::endl;
  std::cout << "          - rename \"New Tool\" into findent" << std::endl;
  std::cout << "          - put " << std::endl;
  std::cout << "               findent-gedit" << std::endl;
  std::cout << "            in the tool" << std::endl;
  std::cout << "          Shortcut Key:  <Alt>F11   (or something more to your liking)" << std::endl;
  std::cout << "          Save:          Nothing" << std::endl;
  std::cout << "          Input:         Current document" << std::endl;
  std::cout << "          Output:        Replace current document" << std::endl;
  std::cout << "          Applicability: All documents   Fortran 95" << std::endl;
  std::cout << "          " << std::endl;
  std::cout << "    ----------------------- " << std::endl;
  std::cout << "" << std::endl;
  std::cout << "      Alternatively, if all is well, it would be sufficient to place" << std::endl;
  std::cout << "      the command" << std::endl;
  std::cout << "	 findent -Ia -i3" << std::endl;
  std::cout << "      in the tool, but the script findent-gedit does some sanity checks" << std::endl;
  std::cout << "      to prevent \"oops\" experiences." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "2) as plugin:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  Find the location of the directory where gedit expects the configuration" << std::endl;
  std::cout << "  files, we assume here $HOME/.local/share/gedit/plugins" << std::endl;
  std::cout << "  Enter the following commands:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "##################################################" << std::endl;
  std::cout << "geditroot=$HOME/.local/share/gedit/plugins" << std::endl;
  std::cout << "mkdir -p $geditroot" << std::endl;
  std::cout << "findent --gedit_plugin > $geditroot/findent.plugin" << std::endl;
  std::cout << "findent --gedit_plugin_py > $geditroot/findent.py" << std::endl;
  std::cout << "##################################################" << std::endl;
  std::cout << "" << std::endl;
  std::cout << " in gedit:" << std::endl;
  std::cout << "   (Edit ->) Preferences -> plugins -> check: findent" << std::endl;
  std::cout << "  findent is available in popup menu (right-click) and" << std::endl;
  std::cout << "  shortcut <Ctrl><Alt>i . You can change that in " << std::endl;
  std::cout << "  findent.py, look for the definition of 'shortcut'." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  Advantage of plugin over external tool: gedit scrolls" << std::endl;
  std::cout << "  back to point where you called findent." << std::endl;
  std::cout << "" << std::endl;
  std::cout << "Flags for findent:" << std::endl;
  std::cout << "" << std::endl;
  std::cout << "  Both the external command as the plugin pass the environment" << std::endl;
  std::cout << "  variable GEDIT_FINDENT_FLAGS to findent. Example: if you" << std::endl;
  std::cout << "  want general indentation set to 2 but indentation of do-loops" << std::endl;
  std::cout << "  set to 4, specify:" << std::endl;
  std::cout << "    export GEDIT_FINDENT_FLAGS=\"-i2 -d4\"" << std::endl;
  std::cout << "  Use" << std::endl;
  std::cout << "    findent -h" << std::endl;
  std::cout << "  for a list of flags." << std::endl;
