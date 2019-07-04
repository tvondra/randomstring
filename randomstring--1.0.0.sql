/* randomstring--1.0.sql */

-- complain if script is sourced in psql, rather than via CREATE EXTENSION
\echo Use "CREATE EXTENSION randomstring" to load this file. \quit

CREATE FUNCTION random_string(int) RETURNS text
AS 'MODULE_PATHNAME', 'random_string'
LANGUAGE C STRICT;

CREATE FUNCTION random_bytea(int) RETURNS bytea
AS 'MODULE_PATHNAME', 'random_bytea'
LANGUAGE C STRICT;
