using System;
using System.Collections.Generic;
using System.Data.SqlClient;

namespace directedge
{
    class Program
    {
        static void Main(string[] args)
        {
            SqlCommand command;
            SqlDataReader reader;
            SqlConnection connection;
            string sqlGetString = "SELECT * FROM Lot_Accrual ORDER BY issue_id, accrual_begin_date;";
            string connectionstring = GetConnectionString();
    
            List<DateTime> accrualDates;
            List<DateInterval> tmpSet = new List<DateInterval>();
            Dictionary<int,List<DateInterval>> entireSet = new Dictionary<int,List<DateInterval>> ();      
            Dictionary<int, List<DateTime>> singleDates = new Dictionary<int, List<DateTime>>(); 

            using (connection = new SqlConnection(connectionstring))
            {
                int previous_id=0, id, amount;
                DateTime begin, end;
                bool isFirstTime = true;

                connection.Open();
                command = new SqlCommand(sqlGetString, connection);
                reader = command.ExecuteReader();
               
                while (reader.Read())
                {
                    id    = (int) reader["issue_id"]; 
                    amount= (int) reader["par_amount"];
                    begin = (DateTime) reader["accrual_begin_date"]; 
                    end   = (DateTime) reader["accrual_end_date"];

                    if (singleDates.TryGetValue(id, out accrualDates))
                    {
                    // key exists 

                        accrualDates.Add(begin);
                        accrualDates.Add(end);
                        tmpSet.Add(new DateInterval(begin, end, id, amount));
                    }
                    else{
                    // key not exist 
                        accrualDates = new List<DateTime>();
                        accrualDates.Add(begin);
                        accrualDates.Add(end);
                        singleDates.Add(id, accrualDates);

                        if (isFirstTime == true){
                        // handle first iteration
                            isFirstTime = false;
                            tmpSet.Add(new DateInterval(begin, end, id, amount));
                            
                            // new key added
                            entireSet.Add(id,tmpSet);
                            previous_id = id; 
                        }
                        else
                        {                         
                            tmpSet = new List<DateInterval>();
                            tmpSet.Add(new DateInterval(begin, end, id, amount));
                            
                            // new list, new key
                            entireSet.Add(id, tmpSet);
                        }
                    }
                    previous_id = id;
 
                }
                connection.Close();
            }

            bool isOverlap;
            List<DateTime> singleDatePoint;
            List<DateInterval> overlapIntervals;
            List<DateIntervalRange> noOverlapIntervals =  new List<DateIntervalRange>();
        
            foreach (KeyValuePair<int, List<DateTime>> SingleDatekvp in singleDates)
            {

                singleDatePoint = SingleDatekvp.Value; singleDatePoint.Sort();
                DateIntervalRange noOverlapInterval;
                for (int i = 0, j = 1; j != singleDatePoint.Count; ++i, ++j)
                {
                    noOverlapInterval = new DateIntervalRange(singleDatePoint[i], singleDatePoint[j]);
                    noOverlapInterval.IssueId = SingleDatekvp.Key;

                    overlapIntervals = entireSet[SingleDatekvp.Key];
                    foreach (DateInterval overlapInterval in overlapIntervals)
                    {
                        isOverlap = overlapInterval.overlapswith(noOverlapInterval);
                        if (!isOverlap) continue;

                        noOverlapInterval.Amount += overlapInterval.Amount;
                    }
                    if (noOverlapInterval.Amount == 0) continue;
                    noOverlapIntervals.Add(noOverlapInterval);
                }
            }

            string sqlPutString = 
                "INSERT INTO Issue_Accrual(issue_id, accrual_begin_date, accrual_end_date, par_amount) "
                + "Values(@id,@begin_date,@end_date,@amount)";
            using (connection = new SqlConnection(connectionstring))
            {

                connection.Open();
                command = new SqlCommand(sqlPutString, connection);

                foreach (DateIntervalRange noOverlapInterval in noOverlapIntervals)
                {
                    command.Parameters.AddWithValue("@id", noOverlapInterval.IssueId);
                    command.Parameters.AddWithValue("@begin_date", noOverlapInterval.BeginDate);
                    command.Parameters.AddWithValue("@end_date", noOverlapInterval.EndDate);
                    command.Parameters.AddWithValue("@amount", noOverlapInterval.Amount);
                    Int32 result = command.ExecuteNonQuery();
                    Console.WriteLine("Rows affected {0} ", result);
                    command.Parameters.Clear();
                }
                connection.Close();
            }
        }

 
        static string GetConnectionString()
        { //testing purposes - move to config file
            return @"Data Source=.\SQLEXPRESS;AttachDbFilename=C:\Documents and Settings\"
                  + @"Administrator\My Documents\localhost.mdf;"
                  + @"Integrated Security=True;Connect Timeout=30;User Instance=True";
        }
    }
}
