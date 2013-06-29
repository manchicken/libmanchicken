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

#ifndef __DYNAMIC_CSV_H__
#define __DYNAMIC_CSV_H__

#include <stdio.h>
#include <dynamic_list.h>
#include <mutable_string.h>

// Think of a header row in a spreadsheet table
typedef struct {
  int index;
  mutable_string_t heading;
} csv_column_t;

// This is the rows
typedef struct {
  int index;
  dynamic_list_t *headings;
  dynamic_list_t cells;
} csv_row_t;

// Think of a cell in a spreadsheet, has a reference to its row and its column
typedef struct {
  csv_column_t *column;
  csv_row_t *row;
  mutable_string_t data;
} csv_cell_t;

// This is the whole document, incl. the file stream pointer
typedef struct {
  FILE *instream;
  char in_quote;
  mutable_string_t quote_buffer;
  mutable_string_t buffer;

  char has_header_row;
  dynamic_list_t cols;
  dynamic_list_t rows;
} csv_document_t;

/* Column stuff */
csv_column_t* csv_column_init(csv_column_t *col);
void csv_column_free(csv_column_t *col);

/* Row stuff */
csv_row_t* csv_row_init(csv_row_t *row, csv_row_t *ro_header);
void csv_row_free(csv_row_t *row);

/* Cell stuff */
csv_cell_t* csv_cell_init(csv_cell_t *cell, csv_row_t *ro_row, csv_col_t *ro_col);
void csv_cell_free(csv_cell_t *cell);

/* Document stuff */
csv_document_t* csv_document_init(csv_document_t *doc, FILE *instream, char first_row_has_headers);
void csv_document_free(csv_document_t *doc);

#endif /* __DYNAMIC_CSV_H__ */