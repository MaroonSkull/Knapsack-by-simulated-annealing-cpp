FROM archlinux:latest

EXPOSE 8080

ARG USERNAME=username
ARG GROUPNAME=groupname
ARG USER_UID=1000
ARG USER_GID=$USER_UID
ARG WORKSPACE=/workspace
ARG PACKAGE_MANAGER=yay
ARG COUNTRY=Russia

# Create the user
RUN groupadd --gid $USER_GID $GROUPNAME \
    && useradd --uid $USER_UID --gid $USER_GID -m $USERNAME -p "" \
		&& usermod -aG wheel $USERNAME \
		&& mkdir -p /etc/sudoers.d/ \
		&& echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
		&& chmod 0440 /etc/sudoers.d/$USERNAME
		
# get ready mirrorlist
RUN pacman -Sy --noconfirm reflector rsync
RUN reflector --latest 10 --sort rate --save /etc/pacman.d/mirrorlist --country $COUNTRY

# install base
RUN pacman -S --noconfirm --needed sudo git openssh git base-devel

# speedup makepkg builds by using all cores available on the host machine.
RUN sed -i '/MAKEFLAGS=/s/^/#/' /etc/makepkg.conf && \
		echo "MAKEFLAGS=\"-j$(nproc)\"" >> /etc/makepkg.conf

USER $USERNAME
WORKDIR /home/$USERNAME
RUN if [ "$PACKAGE_MANAGER" = "yay" ]; then \
			git clone https://aur.archlinux.org/yay.git && \
			cd yay && \
			makepkg -si --noconfirm && \
			yay -Sy --noconfirm yay && \
			cd .. && \
			rm -rf yay; \
		else \
			export PACKAGE_MANAGER="sudo pacman"; \
		fi

# instal cpp tools and other dev stuff
RUN ${PACKAGE_MANAGER} -Syyuu --noconfirm \
		clang \
		llvm \
		gcc \
		gdb \
		cmake \
		ninja \
		ccache \
		doxygen \
		valgrind

# ********************************************************
# * Anything else you want to do like clean up goes here *
# ********************************************************

RUN ${PACKAGE_MANAGER} -S --noconfirm \
		npm \
		jre11-openjdk-headless \
		icu

USER root

RUN npm install @openapitools/openapi-generator-cli -g
RUN openapi-generator-cli version

USER $USERNAME

RUN ${PACKAGE_MANAGER} -Sy --noconfirm \
		boost \
		pistache-git # AUR, don't yet work with pacman

CMD ["sleep", "infinity"]