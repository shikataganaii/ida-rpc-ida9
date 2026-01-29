#pragma once

#define STRINGIFY_IDA_INPUT_FIELD( field_identifier_str, field_id ) field_identifier_str #field_id
#define DROPDOWN_FIELD( field_id ) STRINGIFY_IDA_INPUT_FIELD( "b", field_id ) // lowercase b is dropdown see https://www.hex-rays.com/products/ida/support/sdkdoc/group___f_o_r_m___c.html for reference

namespace ida_utils
{
	// Static buffers to avoid returning local variable addresses
	static char s_filename[ MAXSTR ];
	static char s_processor_module[ MAXSTR ];
	static char s_func_name[ MAXSTR ];

	bool is_idb_loaded( ) {
		const char* path = get_path( PATH_TYPE_IDB );
		return ( path != NULL && strlen( path ) != 0 );
	}

	const char* get_current_filename( ) {
		ssize_t read_size = get_root_filename( s_filename, sizeof( s_filename ) );
		if ( read_size > 0 ) {
			return s_filename;
		}
		return "(unknown)";
	}

	const char* get_current_processor_module( ) {
		if ( get_idp_name( s_processor_module, sizeof( s_processor_module ) ) != NULL ) {
			return s_processor_module;
		}
		return "(unknown)";
	}

	ea_t get_current_cursor_address( ) {
		ea_t cur_addr = get_screen_ea( );
		if ( cur_addr != BADADDR && is_code( get_flags( cur_addr ) ) ) {
			return cur_addr;
		}
		return BADADDR;
	}

	ea_t get_current_function_start_address( ) {
		ea_t cur_addr = get_current_cursor_address( );
		if ( cur_addr == BADADDR ) {
			return BADADDR;
		}

		func_t *func = get_func( cur_addr );
		if ( func != NULL ) {
			return func->start_ea;
		}
		return BADADDR;
	}

	const char* get_current_function_name( ) {
		ea_t cur_addr = get_current_cursor_address( );
		if ( cur_addr == BADADDR ) {
			return NULL;
		}

		func_t *func = get_func( cur_addr );
		if ( func != NULL ) {
			qstring func_name;
			ssize_t size_read = get_func_name( &func_name, func->start_ea );
			if ( size_read > 0 ) {
				qstrncpy( s_func_name, func_name.c_str(), sizeof( s_func_name ) );
				return s_func_name;
			}
		}
		return NULL;
	}
}
