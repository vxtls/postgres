-- Tests with extended query protocol

SET pg_stat_statements.track_utility = FALSE;

-- This test checks that an execute message sets a query ID.
SELECT query_id IS NOT NULL AS query_id_set
  FROM pg_stat_activity WHERE pid = pg_backend_pid() \bind \g