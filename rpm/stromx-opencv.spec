#
# spec file for package [spectemplate]
#
# Copyright (c) 2010 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

# norootforbuild

Name:           libstromx-opencv
Version:        0.1.0
Release:        0
Summary:        Stromx operators for OpenCV functions
Group:          Development/Libraries/C and C++

License:        Apache License 2.0
URL:            http://www.stromx.org
Source0:        %{name}-%{version}.tar.bz2
# BuildArch:      noarch

BuildRequires:  cmake gcc-c++ stromx-devel opencv-devel cppunit-devel
# Requires:       

%description
This package contains stromx operators for many functions of the OpenCV library.

%package        -n stromx-opencv-devel
Summary:        Development files for stromx-opencv
Group:          Development/Libraries/C and C++
Requires:       %{name}%{?_isa} = %{version}-%{release}

%description    -n stromx-opencv-devel
This package contains libraries and header files for
developing applications that use stromx-opencv.

%prep
%setup -q


%build
%{__mkdir} build
cd build
cmake -DCMAKE_INSTALL_PREFIX='%{_prefix}' \
      -DCMAKE_BUILD_TYPE=Release \
%if "%{?_lib}" == "lib64"
      -DLIB_SUFFIX=64 \
%endif
      ..

make %{?_smp_mflags}


%check
cd build
make test ARGS="-V"


%install
cd build
make install DESTDIR=%{buildroot}
find %{buildroot} -name '*.la' -exec rm -f {} ';'


%clean
rm -rf %{buildroot}


%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(0644, root, root, 0755)
%doc
%{_libdir}/*.so.*

%files -n stromx-opencv-devel
%defattr(0644, root, root, 0755)
%doc
%{_includedir}/*
%{_libdir}/*.so

%changelog
