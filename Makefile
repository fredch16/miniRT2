# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredchar <fredchar@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 13:42:12 by apregitz          #+#    #+#              #
#    Updated: 2025/10/13 14:19:32 by fredchar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME :=		miniRT

CC :=		cc
CFLAGS :=	-Wall -Wextra -Werror -g -Ofast
LDFLAGS :=	-lmlx42 -lglfw -lGL -lm -ldl -pthread
LIBFT :=	include/libft/libft.a
LIBMLX :=	include/MLX42

INC :=		-Iinclude -Iinclude/libft -I/usr/local/include
SRCD :=		src
OBJD :=		obj

SRCS :=		$(SRCD)/main.c \

OBJS :=		$(SRCS:$(SRCD)/%.c=$(OBJD)/%.o)

# Create object subdirectories
OBJ_DIRS :=	$(OBJD) \
			$(OBJD)/lexical_analysis \

all: libmlx $(NAME)

libmlx:
	@cd $(LIBMLX) && cmake . -B build && make -C build -j4

$(NAME): $(OBJ_DIRS) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBMLX)/build/libmlx42.a $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C include/libft

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)
	@echo "Compiling miniRT"

$(OBJD)/%.o: $(SRCD)/%.c
	@$(eval TOTAL := $(words $(SRCS)))
	@$(eval PROGRESS := $(shell echo $$(($(PROGRESS)+1))))
	@$(eval PERCENT := $(shell echo $$(($(PROGRESS)*100/$(TOTAL)))))
	@$(call progress_bar,$(PERCENT))
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@$(MAKE) -C include/libft clean
	@rm -rf $(OBJD)

fclean: clean
	@$(MAKE) -C include/libft fclean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

RED     := $(shell tput setaf 1)
GREEN   := $(shell tput setaf 2)
YELLOW  := $(shell tput setaf 3)
BLUE    := $(shell tput setaf 4)
MAGENTA := $(shell tput setaf 5)
CYAN    := $(shell tput setaf 6)
WHITE   := $(shell tput setaf 7)
RESET   := $(shell tput sgr0)

define progress_bar
	@printf "$(CYAN)["; \
	for i in $(shell seq 1 50); do \
		if [ $$i -le $$(($(1)*50/100)) ]; then \
			printf "$(GREEN)█$(RESET)"; \
		else \
			printf "$(WHITE)░$(RESET)"; \
		fi; \
	done; \
	printf "$(CYAN)] %3d%%$(RESET)\r" $(1);
endef