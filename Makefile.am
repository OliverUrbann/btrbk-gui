SUBDIRS = src

EXTRA_DIST=  \
    $(private_icons) \
	  $(NULL)

private_icons = \
  icons/backup.svg \
  icons/backup-err.svg \
  icons/backup-ok.svg \
  icons/backup-running.svg \
  $(NULL)

glade_files = \
  infowin.glade

install-icons:
	for icon in $(private_icons); do \
		mkdir -p $(DESTDIR)$(pkgdatadir)/icons/; \
		$(INSTALL_DATA) $(srcdir)/$$icon $(DESTDIR)$(pkgdatadir)/icons/; \
	done; \
	mkdir -p $(DESTDIR)$(datadir)/icons/hicolor/scalable/apps/; \
	$(INSTALL_DATA) icons/btrbkgui.svg $(DESTDIR)$(datadir)/icons/hicolor/scalable/apps/

install-glade:
	for gf in $(glade_files); do \
		mkdir -p $(DESTDIR)$(pkgdatadir)/; \
		$(INSTALL_DATA) $(srcdir)/$$gf $(DESTDIR)$(pkgdatadir)/; \
	done

install-desktop:
	mkdir -p $(DESTDIR)$(datadir)/applications; \
	$(INSTALL_DATA) btrbkgui.desktop $(DESTDIR)$(datadir)/applications

install-scripts:
	mkdir -p $(DESTDIR)$(pkgdatadir)/; \
	$(INSTALL_DATA) execute_btrbk.sh $(DESTDIR)$(pkgdatadir)/execute_btrbk.sh; \
	chmod +x $(DESTDIR)$(pkgdatadir)/execute_btrbk.sh

install-data-local: install-icons install-glade install-desktop install-scripts
