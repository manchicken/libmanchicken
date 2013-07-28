/*
 * Copyright (c) 2013, Michael D. Stemle, Jr.
 * libmanchicken - All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, this list
 * of conditions and the following disclaimer.
 * 
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or other
 * materials provided with the distribution.
 * Neither the name of Michael D. Stemle, Jr., notsosoft.net, nor the names of its
 * contributors may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
*/

#include <swansong.h>
#include <dynamic_csv.h>

/* Column stuff */
csv_column_t* csv_column_init(csv_column_t *col) {
  col->index = 0;
  if (!mutable_string_init( &(col->heading) )) {
    return NULL;
  }

  return col;
}
void csv_column_free(csv_column_t *col) {
  if (!col) { return; }

  col->index = -1;
  mutable_string_free( &(col->heading) );

  return;
}

/* Row stuff */
csv_row_t* csv_row_init(csv_row_t *row, dynamic_list_t *ro_header) {
  if (!dynamic_list_init( &(row->cells), sizeof(csv_cell_t) )) {
    return NULL;
  }
  // ro_ indicates a variable which I don't touch in the function, but do use the value or reference
  row->headings = ro_header;

  row->index = 0;

  return row;
}
void csv_row_free(csv_row_t *row) {
  if (!row) { return; }

  dynamic_list_free( &(row->cells) );
  row->headings = NULL;
}

/* Cell stuff */
csv_cell_t* csv_cell_init(csv_cell_t *cell, csv_row_t *ro_row, csv_column_t *ro_col) {
  if (!ro_row || !ro_col) {
    swansong("No row or cell passed in to csv_cell_init()", SWANSONG_FATAL);
  }

  if (!mutable_string_init( &(cell->data) )) {
    return NULL;
  }

  cell->row = ro_row;
  cell->column = ro_col;

  return cell;
}
void csv_cell_free(csv_cell_t *cell) {
  if (!cell) { return; }

  cell->row = NULL;
  cell->column = NULL;
  mutable_string_free( &(cell->data) );

  return;
}

/* Document stuff */
csv_document_t* csv_document_init(csv_document_t *doc, FILE *instream, char first_row_has_headers) {
  if (!instream) {
    swansong("Invalid file stream passed in to csv_document_init()", SWANSONG_FATAL);
  }

  doc->instream = instream;
  doc->has_header_row = first_row_has_headers;

  if (!mutable_string_init( &(doc->quote_buffer) )) {
    return NULL;
  }

  if (!mutable_string_init( &(doc->buffer) )) {
    return NULL;
  }

  if (!dynamic_list_init( &(doc->cols), sizeof(csv_column_t) )) {
    return NULL;
  }

  if (!dynamic_list_init( &(doc->rows), sizeof(csv_row_t) )) {
    return NULL;
  }
  
  return doc;
}
void csv_document_free(csv_document_t *doc) {
  if (!doc) { return; }

  doc->instream = NULL;
  doc->in_quote = 'N';

  mutable_string_free( &(doc->quote_buffer) );
  mutable_string_free( &(doc->buffer) );

  dynamic_list_free( &(doc->cols) );
  dynamic_list_free( &(doc->rows) );
}
