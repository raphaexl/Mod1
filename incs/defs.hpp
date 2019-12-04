/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:22:30 by ebatchas          #+#    #+#             */
/*   Updated: 2019/12/04 14:39:49 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <GL/glew.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_opengl.h>
# include <SDL2/SDL_image.h>
# include <glm/glm.hpp>
# include <glm/gtc/matrix_transform.hpp>
# include <glm/gtx/transform.hpp>
# include <glm/gtc/constants.hpp>
# ifdef __APPLE__
# include<OpenCL/opencl.h>
# else
# include <CL/cl.h>
#endif
# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <cstring>
# include <cmath>


# define W_W 800
# define W_H 600
# define W_TITLE ("MOD1")
# define SHADER_BUFF_SIZE 1024

# define YAW (-90.0f)
# define PITCH (0.0f)
# define SPEED (15.0f)
# define SENSITIVITY (2.0f)
# define ZOOM (45.0f)

# define IMG_INIT_FLAGS (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF)
# define SKYBOX_RIGHT_IMG ("data/imgs/skybox/right.jpg")
# define SKYBOX_LEFT_IMG ("data/imgs/skybox/left.jpg")
# define SKYBOX_TOP_IMG ("data/imgs/skybox/top.jpg")
# define SKYBOX_BOTTOM_IMG ("data/imgs/skybox/bottom.jpg")
# define SKYBOX_FRONT_IMG ("data/imgs/skybox/front.jpg")
# define SKYBOX_BACK_IMG ("data/imgs/skybox/back.jpg")

# define DEFAULT_TERRAIN_SIZE 64
//# define DEFAULT_TERRAIN_SIZE 20
