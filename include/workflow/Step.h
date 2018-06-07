#ifndef WORKFLOW_STEP_H
#define WORKFLOW_STEP_H

#include <memory>
#include <unordered_map>
#include <vector>
#include "Vertex.h"
#include "WorkflowGraph.h"

namespace workflow {

    class Connection;
    using ConnectionMap = std::unordered_map<std::string, std::shared_ptr<Connection>>;

    /**
     * @brief A step in a workflow.
     * A single step in a workflow containing inputs and outputs. `Steps` can be piped directly to
     * each other if they have only one output and/or input.
     */
    class Step : public Vertex {
    public:

        Step(
            const std::string &name,
            const std::vector<std::string> &input_names = std::vector<std::string>(),
            const std::vector<std::string> &output_names = std::vector<std::string>(),
            std::shared_ptr<WorkflowGraph> graph = std::make_shared<WorkflowGraph>()
        );

        /** @brief Connect this step's output to another step's input.
         *
         * Pipe the single output of this step to the single input of another. If there are multiple
         * outputs or inputs, then an exception will be thrown.
         */
        void pipe(const std::shared_ptr<Step> &target);

        /** @name Step priority getters and setters. */
        /**@{*/
        unsigned int get_priority() const;
        void set_priority(unsigned int priority);
        /**@}*/

        /** @name Synchronisers to mark named inputs and outputs as synchronised. */
        /**@{*/
        void synchronise_inputs(const std::vector<std::string> &input_names);
        void synchronise_outputs(const std::vector<std::string> &output_names);
        bool is_synchronous() const;
        /**@}*/

        /** @name Getters for named inputs and outputs */
        /**@{*/
        /** @brief Get all inputs. */
        std::shared_ptr<ConnectionMap> get_inputs() const;
        /** @brief Get all outputs. */
        std::shared_ptr<ConnectionMap> get_outputs() const;
        /**@}*/

    private:

        unsigned int priority;
        unsigned int sync_group;

        std::shared_ptr<ConnectionMap> inputs;
        std::shared_ptr<ConnectionMap> outputs;

        void reject_duplicates(const std::vector<std::string> &names,
                               const std::string &source) const;

        std::vector<std::string> get_duplicates(const std::vector<std::string> &names) const;

    };
}

namespace std {

    /** @brief Hash object for hashing steps.
     *
     * For example:
     * @code
     * std::unsorted_map<std::shared_ptr<Step>, std::shared_ptr<Job>> jobs;
     * Workflow workflow;
     * std::shared_ptr<Step> step = workflow.add_step("step_name", {"input"}, {"output"});
     * jobs[step] = std::make_shared<Job>();
     * @endcode
     */
    template <>
    struct hash<workflow::Step> {
        size_t operator()(const workflow::Step &step) const {
            return hash<unsigned int>()(step.identifier);
        }
    };

    template <>
    struct hash<std::shared_ptr<workflow::Step>> {
        size_t operator()(const std::shared_ptr<workflow::Step> &step) const {
            return hash<unsigned int>()(step->identifier);
        }
    };
}

#endif //WORKFLOW_STEP_H
