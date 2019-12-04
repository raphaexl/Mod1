# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/29 15:04:48 by ebatchas          #+#    #+#              #
#    Updated: 2019/11/14 18:58:38 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= mod1

CC  = g++

PWD = \"$(shell pwd)\"


SRCDIR   = srcs
OBJDIR   = objs
BINDIR   = .
INCLUDESDIR = incs

LIBGLEWDIR = ~/.brew/Cellar/glew/2.1.0
LIBGLEW_INCLUDEDIR = include
LIBGLEW = $(LIBGLEWDIR)/lib/libGLEW.a
GLMDIR = ~/.brew/Cellar/glm/0.9.9.5/
GLM_INCLUDEDIR = include
LIBGLFWDIR = ~/.brew/Cellar/glfw/3.3
LIBGLFW_INCLUDEDIR = include
LIBGLFW = $(LIBGLFWDIR)/lib/
LIBSDL2DIR = ~/.brew/Cellar/sdl2/2.0.10
LIBSDL2_INCLUDEDIR = include
LIBSDL2 = $(LIBSDL2DIR)/lib/
LIBSDL2_IMAGE_DIR = ~/.brew/Cellar/sdl2_image/2.0.5
LIBSDL2_IMAGE_INCLUDEDIR = include
LIBSDL2_IMAGE = $(LIBSDL2_IMAGE_DIR)/lib/

DONE_COLOR = \x1b[32;01m
EOC = \033[0m

SRCS_NO_PREFIX = main.cpp window.cpp shader.cpp input.cpp camera.cpp cube.cpp\
				 image.cpp skybox.cpp terrain.cpp map.cpp split.cpp sph.cpp vec3.cpp\
				 opencl1.cpp opencl2.cpp cl_func.cpp

INCLUDES_NO_PREFIX = mod1.hpp window.hpp cube.hpp shader.hpp camera.hpp \
					 image.hpp skybox.hpp input.hpp terrain.hpp defs.hpp map.hpp\
					sph.hpp opencl.hpp 

SOURCES = $(addprefix $(SRCDIR)/, $(SRCS_NO_PREFIX))
OBJECTS = $(addprefix $(OBJDIR)/, $(SRCS_NO_PREFIX:%.cpp=%.o))
INCLUDES = $(addprefix $(INCLUDESDIR)/, $(INCLUDES_NO_PREFIX))

INC = -I $(INCLUDESDIR) -I $(GLMDIR)/$(GLM_INCLUDEDIR) -I $(LIBGLFWDIR)/$(LIBGLFW_INCLUDEDIR) \
	  -I $(LIBGLEWDIR)/$(LIBGLEW_INCLUDEDIR) -I $(LIBSDL2DIR)/$(LIBSDL2_INCLUDEDIR) \
	  -I $(LIBSDL2_IMAGE_DIR)/$(LIBSDL2_IMAGE_INCLUDEDIR)

CFLAGS = -DPATH=$(PWD) -Wall -Wextra -Werror $(INC) -std=c++14
LFLAGS = -L $(LIBGLEWDIR)/lib -L $(LIBGLFWDIR)/lib 	 -L $(LIBSDL2DIR)/lib  -L $(LIBSDL2_IMAGE_DIR)/lib \
		 -lm -lGLEW -lglfw -lSDL2 -lSDL2_image -framework OpenGL -framework OpenCL

all:
	@make $(BINDIR)/$(NAME)

$(BINDIR)/$(NAME): $(OBJECTS)
	@$(CC) -o $@ $^ $(CFLAGS) $(LFLAGS)
	@echo "$(DONE_COLOR)$(NAME) linked with success !$(EOC)"

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(INCLUDES)
	@cp $(LIBSDL2_IMAGE_DIR)/include/SDL2/SDL_image.h  $(LIBSDL2DIR)/include/SDL2/
	@mkdir -p $(OBJDIR)
	$(CC) -c $< -o $@ $(CFLAGS) 

clean:
	@rm -f $(OBJECTS)
	@rm -rf $(OBJDIR)
	@echo "$(DONE_COLOR) $(BINDIR)/$(NAME) objs successfully removed !$(EOC)"

fclean: clean
	@rm -f $(BINDIR)/$(NAME)
	@echo "$(DONE_COLOR) $(BINDIR)/$(NAME) files successfully removed !$(EOC)"

re: fclean all

.PHONY: all clean fclean re
