/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:38:00 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 12:54:10 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/mod1.hpp"

Shader::Shader()
{
	f_file_name = std::string("");	
	v_file_name = std::string("");
	program_id = 0;
}

Shader::Shader(std::string v_file_name, std::string f_file_name)
{
	this->f_file_name = f_file_name;
	this->v_file_name = v_file_name;
	this->program_id = 0;
}

void	Shader::Load(std::string v_file_name, std::string f_file_name)
{
	this->f_file_name = f_file_name;
	this->v_file_name = v_file_name;
	Load();
}

void	Shader::Load(void)
{
	std::ifstream	v_file, f_file;
	std::string		v_code, f_code;

	v_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	f_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		std::stringstream v_sstr, f_sstr;

		v_file.open(v_file_name.c_str());
		f_file.open(f_file_name.c_str());
		v_sstr<<v_file.rdbuf();
		f_sstr<<f_file.rdbuf();

		v_code = v_sstr.str();
		f_code = f_sstr.str();
		f_file.close();
		v_file.close();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr<<"Error loading Shader files"<<std::endl;
		exit(-1);
	}
	const char	*v_scode{v_code.c_str()}, *f_scode{f_code.c_str()};
	int			raise;
	char		info[SHADER_BUFF_SIZE];
	GLuint		v_shader, f_shader;

	v_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(v_shader, 1, &v_scode, NULL);
	glCompileShader(v_shader);
	glGetShaderiv(v_shader, GL_COMPILE_STATUS, &raise);
	if (!raise)
	{
		glGetShaderInfoLog(v_shader, SHADER_BUFF_SIZE, NULL, info);
		std::cerr<<"VERTEX SHADER : "<<info<<std::endl;
		exit(EXIT_FAILURE);
	}
	f_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(f_shader, 1, &f_scode, NULL);
	glCompileShader(f_shader);
	glGetShaderiv(f_shader, GL_COMPILE_STATUS, &raise);
	if (!raise)
	{

		glGetShaderInfoLog(f_shader, SHADER_BUFF_SIZE, NULL, info);
		std::cerr<<"FRAGMENT SHADER : "<<info<<std::endl;
		exit(EXIT_FAILURE);
	}
	this->program_id = glCreateProgram();
	glAttachShader(this->program_id, v_shader);
	glAttachShader(this->program_id, f_shader);
	glLinkProgram(this->program_id);
	glGetProgramiv(this->program_id, GL_LINK_STATUS, &raise);
	if (!raise)
	{
		glGetProgramInfoLog(this->program_id, SHADER_BUFF_SIZE, NULL, info);
		std::cerr<<"PROGRAM LINK : "<<info<<std::endl;
		exit(EXIT_FAILURE);
	}
	glDetachShader(this->program_id, f_shader);
	glDetachShader(this->program_id, v_shader);
	glDeleteShader(f_shader);
	glDeleteShader(v_shader);
}

void	Shader::set_bool(std::string name, bool value)
{
	glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), (int)value);
}

void	Shader::set_int(std::string name, int value)
{
	glUniform1i(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void	Shader::set_float(std::string name, float value)
{
	glUniform1f(glGetUniformLocation(this->program_id, name.c_str()), value);
}

void	Shader::set_vec3(std::string name, glm::vec3 value)
{
	glUniform3f(glGetUniformLocation(this->program_id, name.c_str()), value.x, value.y, value.z);
}

void	Shader::set_mat3(std::string name, glm::mat3 value)
{
	glUniformMatrix3fv(glGetUniformLocation(this->program_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

void	Shader::set_mat4(std::string name, glm::mat4 value)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
}

