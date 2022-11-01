# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aguillar <aguillar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 16:58:55 by aguillar          #+#    #+#              #
#    Updated: 2022/10/20 18:31:30 by aguillar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET   = cub3D

CC       = gcc

CFLAGS   = -Wall -Wextra -Werror -g3 -I/usr/include -Imlx_linux -O3

LINKER   = gcc

LFLAGS   =  -L minilibx-linux -lmlx -lXext -lX11 -lm

SRCDIR   = src

OBJDIR   = obj

SOURCES  := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f

$(TARGET): $(OBJECTS)
	@${MAKE} -C ./minilibx-linux
	@$(LINKER) $(OBJECTS) $(LFLAGS) -o $@

$(OBJECTS):	$(OBJDIR)/%.o :	$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	@$(rm) ./minilibx-linux/*.a
	@$(rm) ./minilibx-linux/*.o
	@$(rm) $(OBJECTS)

fclean: clean
	@$(rm) $(TARGET)

re: fclean all

.PHONY: all clean fclean re
