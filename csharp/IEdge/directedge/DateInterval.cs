using System;
using System.Collections.Generic;

namespace directedge
{
    public class DateInterval
    {
        protected DateTime begin, end;
        protected int issue_id, amount;

        public DateInterval(DateTime begin, DateTime end)
        {
            this.begin = begin;
            this.end = end;
        }

        public DateInterval(DateTime begin, DateTime end, int issue_id, int amount)
        {
            this.begin   = begin; 
            this.end     = end;
            this.issue_id= issue_id; 
            this.amount  = amount;
        }
        public bool overlapswith(DateInterval shortIntervalDate)
        {
            return (this.begin <= shortIntervalDate.BeginDate &&
                shortIntervalDate.EndDate <= this.end);
        }
         
        public DateTime BeginDate
        {
            get { return begin; }
        }
        public DateTime EndDate
        {
            get { return end; }
        }
        public virtual int IssueId
        {
            get { return issue_id; }
            set { ;}
        }
        public virtual int Amount
        {
            get{ return amount; }
            set {;}
        } 

    }

    public class DateIntervalRange : DateInterval
    {
        public DateIntervalRange( DateTime begin, DateTime end ) 
            : base(begin, end){ }

        public DateIntervalRange( DateTime begin, DateTime end, int issue_id, int amount )
            : base(begin, end, issue_id, amount) { }

        public override int Amount
        {
            get { return base.amount;}
            set { base.amount = value; }
        }
        public override int IssueId
        {   get { return base.issue_id; }
            set { base.issue_id = value; }
        }

    }
}
