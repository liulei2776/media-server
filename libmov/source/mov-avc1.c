#include "file-reader.h"
#include "file-writer.h"
#include "mov-internal.h"
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

int mov_read_avcC(struct mov_t* mov, const struct mov_box_t* box)
{
	struct mov_track_t* track = mov->track;
	if (track->extra_data_size < box->size)
	{
		void* p = realloc(track->extra_data, box->size);
		if (NULL == p) return ENOMEM;
		track->extra_data = p;
	}

	file_reader_read(mov->fp, track->extra_data, box->size);
	track->extra_data_size = box->size;
	return file_reader_error(mov->fp);
}