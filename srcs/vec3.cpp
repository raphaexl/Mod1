/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 19:02:34 by ebatchas          #+#    #+#             */
/*   Updated: 2019/11/12 19:02:45 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/mod1.hpp"

glm::vec3 vec3(float x, float y, float z)
{
    glm::vec3 res;

    res.x = x;
    res.y = y;
    res.z = z;
    return (res);
}

glm::vec3 vec3_sub(glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3  res;

    res.x = v1.x - v2.x;
    res.y = v1.y - v2.y;
    res.z = v1.z - v2.z;
    return (res);
}

glm::vec3  vec3_sum(glm::vec3 v1, glm::vec3 v2)
{
    glm::vec3 res;

    res.x = v1.x + v2.x;
    res.y = v1.y + v2.y;
    res.z = v1.z + v2.z;
    return (res);
}

glm::vec3  vec3_mult(glm::vec3 v1, glm::vec3 v2)
{
   glm::vec3  res;

    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;
    res.z = v1.z * v2.z;
    return (res);
}

glm::vec3  vec3_normalize(glm::vec3 v)
{
    float   norm;

    norm = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    return (vec3(v.x / norm, v.y / norm, v.z / norm));
}

glm::vec3  vec3_kmult(float k, glm::vec3 v2)
{
    glm::vec3 res;

    res.x = k * v2.x;
    res.y = k * v2.y;
    res.z = k * v2.z;
    return (res);
}

float  vec3_square_norm(glm::vec3 v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

float  vec3_norm(glm::vec3 v)
{
    return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
