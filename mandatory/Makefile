#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 15:51:52 by edbernar          #+#    #+#              #
#    Updated: 2023/11/29 23:59:37 by eddy             ###   ########.fr        #
#                                                                              #
#******************************************************************************#

MAKEFLAGS 		+= --silent

SRCS			=	main.c													\
					graphics/main_graphics.c								\
					graphics/load_textures/load_textures.c					\
					graphics/free_functions/free_all.c						\
					graphics/free_functions/destroy_textures.c				\
					graphics/raycasting/main_raycasting.c					\
					graphics/raycasting/raycast.c							\
					graphics/raycasting/utils.c								\
					graphics/entry/keyboard/keyboard.c						\
					graphics/entry/keyboard/game_keyboard.c					\
					graphics/init/init.c									\
					graphics/update.c										\
					parsing/check_map_lines.c								\
					parsing/check_map_param.c								\
					parsing/parse_file.c									\
					parsing/parse_lines.c									\
					parsing/can_exit_map.c									\
					parsing/set_map_blocks.c								\
					utils/first.c											\
					free_map.c												\

NAME			=	cub3D

OBJS			=	$(addprefix ./.build/, $(SRCS:.c=.o))

OBJ_DIR			=	$(sort $(dir $(OBJS)))

MACROLIBX		=	../Libs/MacroLibX/libmlx.so

LIBFT			=	../Libs/libft/libft.a

CC				=	cc

CFLAGS			=	-Wall -Werror -Wextra -Iincludes -I$(dir $(LIBFT)) -I$(dir $(MACROLIBX))/includes/

TOTAL_SRCS		= 	$(words $(SRCS))

COMPILED_SRCS 	= 	0

all : ${NAME}

./.build/%.o : ./srcs/%.c
	@tput civis
	@$(CC) -c $(CFLAGS) "$<" -o "$@" 
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
        tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
    fi
	@echo "┌───────────────────────────────────────┐\n│\c"
	@if [ "$(COMPILED_SRCS)" -gt "0" ]; then \
        for i in $$(seq 0 $(shell echo "$$((($(COMPILED_SRCS) * 39) / $(TOTAL_SRCS)))")); do \
            printf "█"; \
        done; \
		for i in $$(seq 0 $(shell echo "$$(((($(TOTAL_SRCS) - $(COMPILED_SRCS)) * 39) / $(TOTAL_SRCS) - 1))")); do \
            printf " "; \
        done; \
    fi
	@echo "│\n└───────────────────────────────────────┘"
	@echo "[ $$(expr \( $(COMPILED_SRCS) \* 100 \) / $(TOTAL_SRCS))% ]\033[32m $< \033[0m"
	$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@tput cnorm

$(LIBFT) :
	@make -C "$(dir $(LIBFT))"

$(MACROLIBX) :
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" -j
	@echo "────────────────────────────────"

$(OBJ_DIR):
	@mkdir -p $@

${NAME} : $(MACROLIBX) $(LIBFT) $(OBJ_DIR) ${OBJS}
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
        tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
		tput cuu1; \
		tput el; \
    fi
	@if [ "$(COMPILED_SRCS)" -ne "0" ]; then \
        echo "┌───────────────────────────────────────┐"; \
		echo "│███████████████████████████████████████│"; \
		echo "└───────────────────────────────────────┘"; \
		$(CC) ${OBJS} -o ${NAME} $(MACROLIBX) ${CFLAGS} -L$(dir $(LIBFT)) -lft -lm -lSDL2; \
		echo "[ 100% ]\033[32m Compilation $(NAME) completed !\033[0m"; \
		echo "\n\033[32mThe program \"$(NAME)\" is ready !\033[0m"; \
	else \
		echo "\033[32mThe program \"$(NAME)\" is already ready !\033[0m"; \
    fi

clean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" clean
	@echo "── CUB3D ───────────────────────"
	@make -C "$(dir $(LIBFT))" clean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build

fclean :
	@rm -f ${OBJS}
	@echo "── MLX ─────────────────────────"
	@make -C "$(dir $(MACROLIBX))" fclean
	@echo "── CUB3D ───────────────────────"
	@rm -f ${NAME}
	@make -C "$(dir $(LIBFT))" fclean
	@echo "Files successfully cleaned."
	@echo "────────────────────────────────"
	@rm -rf .build

re	: fclean all

recub :
	@rm -f ${OBJS}
	@rm -f ${NAME}
	@echo "Files successfully cleaned (only cub3d's files)."
	@make all

-include $(OBJS:.o=.d)

.PHONY : libft mlx re fclean all clean create $(NAME)
