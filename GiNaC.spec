%define name ginac
%define version 1.8.5
%define release 1

Summary: C++ library for symbolic calculations
Name: %{name}
Version: %{version}
Release: %{release}
License: GPL
Group: System Environment/Libraries
Source0: https://www.ginac.de/%{name}-%{version}.tar.bz2
URL: https://www.ginac.de/
BuildRoot: %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Prefix: %{_prefix}

Requires(post): /sbin/install-info
Requires(preun): /sbin/install-info
Requires: cln >= 1.1
BuildRequires: cln-devel >= 1.1 gcc-c++ readline-devel
Obsoletes: GiNaC

%description
GiNaC (which stands for "GiNaC is Not a CAS (Computer Algebra System)") is an
open framework for symbolic computation within the C++ programming language.


%package devel
Summary: GiNaC development libraries and header files
Group: Development/Libraries
Requires: %{name} = %{version}-%{release} cln-devel
Obsoletes: GiNaC-devel

%description devel
GiNaC (which stands for "GiNaC is Not a CAS (Computer Algebra System)") is an
open framework for symbolic computation within the C++ programming language.

This package contains the libraries, include files and other resources you
use to develop GiNaC applications.


%package utils
Summary: GiNaC-related utilities
Group: System Environment/Libraries
Requires: %{name} = %{version}-%{release}
Obsoletes: GiNaC-utils

%description utils
GiNaC (which stands for "GiNaC is Not a CAS (Computer Algebra System)") is an
open framework for symbolic computation within the C++ programming language.

This package includes the ginsh ("GiNaC interactive shell") which provides a
simple and easy-to-use CAS-like interface to GiNaC for non-programmers, and
the tool "viewgar" which displays the contents of GiNaC archives.


%prep
%setup -q

%build
%configure
make

%install
rm -rf ${RPM_BUILD_ROOT}
%makeinstall

%clean
rm -rf ${RPM_BUILD_ROOT}

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%post devel
/sbin/install-info --info-dir=%{_infodir} %{_infodir}/ginac.info.gz 2>/dev/null || :

%preun devel
if [ "$1" = 0 ]; then
  /sbin/install-info --delete --info-dir=%{_infodir} %{_infodir}/ginac.info.gz 2>/dev/null || :
fi

%files
%defattr(-,root,root)
%doc AUTHORS COPYING ChangeLog NEWS README
%{_libdir}/*.so.*

%files devel
%defattr(-,root,root)
%{_libdir}/*.a
%{_libdir}/*.la
%{_libdir}/*.so
%{_libdir}/pkgconfig/ginac.pc
%{_includedir}/ginac
%{_infodir}/*.info*

%files utils
%defattr(-,root,root)
%{_bindir}/ginsh
%{_bindir}/viewgar
%{_mandir}/man1/ginsh.1*
%{_mandir}/man1/viewgar.1*

%changelog
* Mon Jul 11 2005 Christian Bauer <Christian.Bauer@uni-mainz.de>
- name of package changed from "GiNaC" to "ginac"; added "Obsoletes:"
  directives

* Thu Jun 30 2005 Christian Bauer <Christian.Bauer@uni-mainz.de>
- included some updates from the Fedora Extras spec file:
  - "Copyright:" -> "License:"
  - Fixed broken install-info command
  - Added missing BuildRequires
  - Added release to Requires for devel and utils
  - Remove processing of info files (this is supposed to be automatic)
  - Added cln-devel as dependency of GiNaC-devel

* Thu Nov 20 2003 Christian Bauer <Christian.Bauer@uni-mainz.de>
- added pkg-config metadata file to devel package

* Thu Nov  1 2001 Christian Bauer <Christian.Bauer@uni-mainz.de>
- moved ginsh and viewgar to "utils" package

* Thu Oct  5 2000 Christian Bauer <Christian.Bauer@uni-mainz.de>
- cleaned up a bit

* Wed Jan 26 2000 Christian Bauer <Christian.Bauer@uni-mainz.de>
- split into user and devel packages

* Wed Dec  1 1999 Christian Bauer <Christian.Bauer@uni-mainz.de>
- aclocal macros get installed
