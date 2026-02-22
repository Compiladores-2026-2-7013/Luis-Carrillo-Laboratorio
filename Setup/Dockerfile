# Usamos Ubuntu como base
FROM ubuntu:22.04

# Evitar prompts interactivos durante la instalación
ENV DEBIAN_FRONTEND=noninteractive

# 1. Instalar herramientas de compilación y utilidades solicitadas
RUN apt-get update && apt-get install -y \
    build-essential \
    binutils \
    less \
    nano \
    git \
    && apt-get clean

# 2. Instalar XFCE, XRDP (entorno gráfico) y utilidades básicas
RUN apt-get update && apt-get install -y \
    xfce4 \
    xfce4-goodies \
    xrdp \
    sudo \
    dbus-x11 \
    x11-xserver-utils \
    && apt-get clean

# Configurar XRDP para usar XFCE
RUN echo "xfce4-session" > /etc/skel/.Xclients

RUN touch /etc/xrdp/Xwrapper.config && \
    echo "allowed_users=anybody" > /etc/xrdp/Xwrapper.config

# Crear usuario
RUN useradd -m -s /bin/bash docker_user && \
    echo "docker_user:docker_passwd" | chpasswd && \
    adduser docker_user sudo

EXPOSE 3389

# Usar formato JSON para CMD (evita el warning y maneja mejor señales de cierre)
CMD ["/bin/bash", "-c", "service dbus start && service xrdp start && tail -f /var/log/xrdp.log"]


# TO RUN container:
# docker run -d \
#  --name entorno-compiladores \
#  -p 3389:3389 \
#  -v "/absolute/path/to/directory/in/host:/home/docker/proyectos" \
#  --shm-size="1gb" \
#  compiladores2026
