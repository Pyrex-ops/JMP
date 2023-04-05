FROM php:8.2.4-apache
RUN apt-get update && \ docker-php-ext-install mysqli pdo pdo_mysql

FROM mysql:latest
USER root
RUN chmod 755 /var/lib/mysql