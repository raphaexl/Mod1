/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 16:33:31 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/02 13:10:24 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "image.hpp"

class	Shader
{
	private:
		GLuint			program_id;
		std::string		f_file_name;
		std::string		v_file_name;
	public:
		Shader();
		Shader(std::string v_file_name, std::string f_file_name);
		void	Load(std::string v_file_name, std::string f_file_name);
		void	Load(void);
		void	Use(void){if (glIsProgram(program_id))glUseProgram(program_id);};
		void	set_bool(std::string name, bool value);
		void	set_int(std::string name, int value);
		void	set_float(std::string name, float value);
		void	set_vec3(std::string name, glm::vec3 value);
		void	set_mat3(std::string name, glm::mat3 value);
		void	set_mat4(std::string name, glm::mat4 value);
		~Shader(){if (glIsProgram(program_id))glDeleteProgram(program_id);};
};
