#ifndef SHAND_FILE_MAPPING_CONTAINER_INCLUDE
#define SHAND_FILE_MAPPING_CONTAINER_INCLUDE

// Shand File Mapping Container
//
// Copyright Akira Takahashi 2011
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_DATE_TIME_NO_LIB)
	#define BOOST_DATE_TIME_NO_LIB
#endif

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>

namespace shand {

namespace ipc = boost::interprocess;

template <class T>
class file_mapping_container {
public:
	typedef ipc::allocator<T, ipc::managed_mapped_file::segment_manager> allocator_t;
	typedef ipc::vector<T, allocator_t> container_t;

	file_mapping_container(
			ipc::create_only_t create_only,
			const std::string& filename,
			std::size_t filesize,
			const std::string& object_name)
		: managed_file_(create_only, filename.c_str(), filesize),
		  allocator_(managed_file_.get_segment_manager()),
		  container_(*(managed_file_.construct<container_t>(object_name.c_str())(allocator_)))
	{}

	file_mapping_container(
			ipc::open_only_t open_only,
			const std::string& filename,
			const std::string& object_name)
		: managed_file_(open_only, filename.c_str()),
		  allocator_(managed_file_.get_segment_manager()),
		  container_(*(managed_file_.find<container_t>(object_name.c_str()).first))
	{
	}

	file_mapping_container(
			ipc::open_or_create_t open_or_create,
			const std::string& filename,
			std::size_t filesize,
			const std::string& object_name)
		: managed_file_(open_or_create, filename.c_str(), filesize),
		  allocator_(managed_file_.get_segment_manager()),
		  container_(*(managed_file_.find_or_construct<container_t>(object_name.c_str())(allocator_)))
	{}

	container_t& get() { return container_; }
	const container_t& get() const { return container_; }

private:
	ipc::managed_mapped_file managed_file_;
	allocator_t allocator_;
	container_t& container_;
};

} // namespace shand

#endif // SHAND_FILE_MAPPING_CONTAINER_INCLUDE

