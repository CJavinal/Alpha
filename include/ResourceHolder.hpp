#pragma once
#ifndef ResourceHolder_HPP_INCLUDED
#define ResourceHolder_HPP_INCLUDED
#include <cassert>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder {
	public:
		void				load(Identifier id, const std::string& filename); 
		template <typename Parameter>
		void				load(Identifier id, const std::string& filename,
									const Parameter& secondParam);
		Resource&			get(Identifier id);
		const Resource&		get(Identifier id) const;
	
	private:
		void				insertResource(Identifier id,
									std::unique_ptr<Resource> resource);
	
	private:
		std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"
#include "ResourceIdentifiers.hpp"
#endif // ResourceHolder_HPP_INCLUDED
